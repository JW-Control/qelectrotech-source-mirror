/*
		Copyright 2006-2026 QElectroTech Team
		This file is part of QElectroTech.

		QElectroTech is free software: you can redistribute it and/or modify
		it under the terms of the GNU General Public License as published by
		the Free Software Foundation, either version 2 of the License, or
		(at your option) any later version.

		QElectroTech is distributed in the hope that it will be useful,
		but WITHOUT ANY WARRANTY; without even the implied warranty of
		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
		GNU General Public License for more details.

		You should have received a copy of the GNU General Public License
		along with QElectroTech.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "propertieseditorfactory.h"

#include "../PropertiesEditor/propertieseditorwidget.h"
#include "../QPropertyUndoCommand/qpropertyundocommand.h"
#include "../diagram.h"
#include "../qetgraphicsitem/ViewItem/projectdbmodel.h"
#include "../qetgraphicsitem/ViewItem/qetgraphicstableitem.h"
#include "../qetgraphicsitem/ViewItem/ui/graphicstablepropertieseditor.h"
#include "../qetgraphicsitem/ViewItem/ui/projectdbmodelpropertieswidget.h"
#include "../qetgraphicsitem/diagramimageitem.h"
#include "../qetgraphicsitem/dynamicelementtextitem.h"
#include "../qetgraphicsitem/element.h"
#include "../qetgraphicsitem/elementtextitemgroup.h"
#include "../qetgraphicsitem/independenttextitem.h"
#include "../qetgraphicsitem/qetshapeitem.h"
#include "../qetinformation.h"
#include "../ui/dynamicelementtextitemeditor.h"
#include "../ui/elementpropertieswidget.h"
#include "../ui/imagepropertieswidget.h"
#include "../ui/inditextpropertieswidget.h"
#include "../ui/shapegraphicsitempropertieswidget.h"

#include <QColor>
#include <QFont>
#include <QGraphicsItem>
#include <QHeaderView>
#include <QLabel>
#include <QLocale>
#include <QSet>
#include <QTabWidget>
#include <QTreeWidget>
#include <QUndoCommand>
#include <QUndoStack>
#include <QVBoxLayout>

namespace {

constexpr int kPropertyRole = Qt::UserRole + 40;
constexpr int kGroupRole = Qt::UserRole + 41;

QString mixedValue()
{
	return QStringLiteral("***");
}

QString textSemanticKey(DynamicElementTextItem *text)
{
	if (!text) {
		return QString();
	}

	switch (text->textFrom())
	{
		case DynamicElementTextItem::ElementInfo:
			return QStringLiteral("info:") + text->infoName();
		case DynamicElementTextItem::CompositeText:
			return QStringLiteral("composite:") + text->compositeText();
		case DynamicElementTextItem::UserText:
		default:
			return QStringLiteral("user");
	}
}

class MultiDynamicTextPropertiesWidget : public PropertiesEditorWidget
{
	public:
		explicit MultiDynamicTextPropertiesWidget(const QList<Element *> &elements,
											 QWidget *parent = nullptr) :
			PropertiesEditorWidget(parent)
		{
			buildGui();
			setElements(elements);
		}

		explicit MultiDynamicTextPropertiesWidget(
				const QList<DynamicElementTextItem *> &texts,
				QWidget *parent = nullptr) :
			PropertiesEditorWidget(parent)
		{
			buildGui();
			setTexts(texts);
		}

		QString title() const override
		{
			return tr("Textos");
		}

		bool setLiveEdit(bool live_edit) override
		{
			m_live_edit = live_edit;
			return true;
		}

		void updateUi() override
		{
			rebuildTree();
		}

	private:
		enum EditProperty {
			NoProperty = 0,
			FontSize,
			TextWidth,
			PositionX,
			PositionY,
			Rotation
		};

		struct TextGroup {
			QList<DynamicElementTextItem *> texts;
		};

		void buildGui()
		{
			auto *main_layout = new QVBoxLayout(this);
			m_summary = new QLabel(this);
			m_summary->setWordWrap(true);
			main_layout->addWidget(m_summary);

			m_tabs = new QTabWidget(this);
			auto *texts_page = new QWidget(m_tabs);
			auto *texts_layout = new QVBoxLayout(texts_page);
			m_tree = new QTreeWidget(texts_page);
			m_tree->setColumnCount(2);
			m_tree->setHeaderLabels(QStringList() << tr("Propiedad") << tr("Valor"));
			m_tree->header()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
			m_tree->header()->setSectionResizeMode(1, QHeaderView::Stretch);
			texts_layout->addWidget(m_tree);
			m_tabs->addTab(texts_page, tr("Textos"));
			main_layout->addWidget(m_tabs);

			connect(m_tree, &QTreeWidget::itemChanged,
					this,
					[this](QTreeWidgetItem *item, int column) {
						handleItemChanged(item, column);
					});
		}

		void setElements(const QList<Element *> &elements)
		{
			m_groups.clear();
			m_selection_count = elements.size();

			if (elements.size() < 2 || !elements.first()) {
				rebuildTree();
				return;
			}

			const QList<DynamicElementTextItem *> reference =
					elements.first()->dynamicTextItems();
			QList<QSet<DynamicElementTextItem *>> used;
			used.reserve(elements.size());
			for (int i = 0; i < elements.size(); ++i) {
				used.append(QSet<DynamicElementTextItem *>());
			}

			for (DynamicElementTextItem *reference_text : reference)
			{
				if (!reference_text) {
					continue;
				}

				TextGroup group;
				group.texts << reference_text;
				used[0].insert(reference_text);
				const QString key = textSemanticKey(reference_text);
				bool compatible = true;

				for (int element_index = 1;
					 element_index < elements.size();
					 ++element_index)
				{
					Element *element = elements.at(element_index);
					if (!element) {
						compatible = false;
						break;
					}

					const QList<DynamicElementTextItem *> candidates =
							element->dynamicTextItems();
					DynamicElementTextItem *match = nullptr;
					for (DynamicElementTextItem *candidate : candidates)
					{
						if (candidate
								&& !used[element_index].contains(candidate)
								&& textSemanticKey(candidate) == key)
						{
							match = candidate;
							break;
						}
					}

					if (!match
							&& reference.size() == 1
							&& candidates.size() == 1
							&& !used[element_index].contains(candidates.first()))
					{
						match = candidates.first();
					}

					if (!match) {
						compatible = false;
						break;
					}

					used[element_index].insert(match);
					group.texts << match;
				}

				if (compatible && group.texts.size() == elements.size()) {
					m_groups << group;
				}
			}

			rebuildTree();
		}

		void setTexts(const QList<DynamicElementTextItem *> &texts)
		{
			m_groups.clear();
			m_selection_count = texts.size();
			TextGroup group;
			for (DynamicElementTextItem *text : texts) {
				if (text) {
					group.texts << text;
				}
			}
			if (group.texts.size() >= 2) {
				m_groups << group;
			}
			rebuildTree();
		}

		template <typename Getter, typename Formatter>
		QString commonValue(const QList<DynamicElementTextItem *> &texts,
							Getter getter,
							Formatter formatter) const
		{
			if (texts.isEmpty()) {
				return QString();
			}

			const auto first = getter(texts.first());
			for (int i = 1; i < texts.size(); ++i) {
				if (!(getter(texts.at(i)) == first)) {
					return mixedValue();
				}
			}
			return formatter(first);
		}

		QString sourceText(DynamicElementTextItem::TextFrom source) const
		{
			switch (source)
			{
				case DynamicElementTextItem::ElementInfo:
					return tr("Información del elemento");
				case DynamicElementTextItem::CompositeText:
					return tr("Texto compuesto");
				case DynamicElementTextItem::UserText:
				default:
					return tr("Texto de usuario");
			}
		}

		QString yesNo(bool value) const
		{
			return value ? tr("Sí") : tr("No");
		}

		QString realText(qreal value) const
		{
			return QString::number(value, 'g', 12);
		}

		QTreeWidgetItem *addRow(QTreeWidgetItem *parent,
								const QString &name,
								const QString &value,
								int group_index,
								EditProperty property = NoProperty)
		{
			auto *row = new QTreeWidgetItem(parent);
			row->setText(0, name);
			row->setText(1, value);
			row->setData(1, kGroupRole, group_index);
			row->setData(1, kPropertyRole, static_cast<int>(property));
			if (property != NoProperty) {
				row->setFlags(row->flags() | Qt::ItemIsEditable);
			}
			return row;
		}

		void rebuildTree()
		{
			if (!m_tree || !m_summary) {
				return;
			}

			m_rebuilding = true;
			m_tree->clear();
			m_summary->setText(
					tr("%1 elementos seleccionados. Los valores distintos se muestran como ***. "
					   "Al editar un valor común, el cambio se aplica a toda la selección.")
							.arg(m_selection_count));

			if (m_groups.isEmpty())
			{
				auto *item = new QTreeWidgetItem(m_tree);
				item->setText(0, tr("Sin textos dinámicos compatibles"));
				item->setFirstColumnSpanned(true);
				m_rebuilding = false;
				return;
			}

			for (int group_index = 0; group_index < m_groups.size(); ++group_index)
			{
				const QList<DynamicElementTextItem *> &texts =
						m_groups.at(group_index).texts;
				if (texts.isEmpty()) {
					continue;
				}

				const QString displayed_text = commonValue(
						texts,
						[](DynamicElementTextItem *text) { return text->toPlainText(); },
						[](const QString &value) { return value; });
				QString title = displayed_text;
				if (title.isEmpty() || title == mixedValue()) {
					title = tr("Texto %1").arg(group_index + 1);
				}
				title += tr(" — %1 elementos").arg(texts.size());

				auto *root = new QTreeWidgetItem(m_tree);
				root->setText(0, title);
				root->setFirstColumnSpanned(true);

				addRow(root,
					   tr("Fuente de texto"),
					   commonValue(
							   texts,
							   [](DynamicElementTextItem *text) { return text->textFrom(); },
							   [this](DynamicElementTextItem::TextFrom value) {
								   return sourceText(value);
							   }),
					   group_index);

				addRow(root,
					   tr("Información"),
					   commonValue(
							   texts,
							   [](DynamicElementTextItem *text) { return text->infoName(); },
							   [](const QString &value) {
								   return value.isEmpty()
										  ? QString()
										  : QETInformation::translatedInfoKey(value);
							   }),
					   group_index);

				addRow(root,
					   tr("Texto mostrado"),
					   commonValue(
							   texts,
							   [](DynamicElementTextItem *text) { return text->toPlainText(); },
							   [](const QString &value) { return value; }),
					   group_index);

				addRow(root,
					   tr("Tamaño"),
					   commonValue(
							   texts,
							   [](DynamicElementTextItem *text) { return text->font().pointSize(); },
							   [](int value) { return QString::number(value); }),
					   group_index,
					   FontSize);

				addRow(root,
					   tr("Tipo de letra"),
					   commonValue(
							   texts,
							   [](DynamicElementTextItem *text) { return text->font().family(); },
							   [](const QString &value) { return value; }),
					   group_index);

				addRow(root,
					   tr("Color"),
					   commonValue(
							   texts,
							   [](DynamicElementTextItem *text) { return text->color(); },
							   [](const QColor &value) { return value.name(); }),
					   group_index);

				addRow(root,
					   tr("Marco"),
					   commonValue(
							   texts,
							   [](DynamicElementTextItem *text) { return text->frame(); },
							   [this](bool value) { return yesNo(value); }),
					   group_index);

				addRow(root,
					   tr("Anchura"),
					   commonValue(
							   texts,
							   [](DynamicElementTextItem *text) { return text->textWidth(); },
							   [this](qreal value) { return realText(value); }),
					   group_index,
					   TextWidth);

				bool positions_available = true;
				for (DynamicElementTextItem *text : texts) {
					if (text->parentGroup()) {
						positions_available = false;
						break;
					}
				}

				if (positions_available)
				{
					addRow(root,
						   tr("Posición X"),
						   commonValue(
								   texts,
								   [](DynamicElementTextItem *text) { return text->pos().x(); },
								   [this](qreal value) { return realText(value); }),
						   group_index,
						   PositionX);

					addRow(root,
						   tr("Posición Y"),
						   commonValue(
								   texts,
								   [](DynamicElementTextItem *text) { return text->pos().y(); },
								   [this](qreal value) { return realText(value); }),
						   group_index,
						   PositionY);
				}

				addRow(root,
					   tr("Rotación"),
					   commonValue(
							   texts,
							   [](DynamicElementTextItem *text) { return text->rotation(); },
							   [this](qreal value) { return realText(value); }),
					   group_index,
					   Rotation);

				addRow(root,
					   tr("Conservar rotación"),
					   commonValue(
							   texts,
							   [](DynamicElementTextItem *text) {
								   return text->keepVisualRotation();
							   },
							   [this](bool value) { return yesNo(value); }),
					   group_index);
			}

			m_tree->expandAll();
			m_rebuilding = false;
		}

		bool parseNumber(const QString &text, qreal *value) const
		{
			if (!value) {
				return false;
			}

			bool ok = false;
			qreal parsed = QLocale().toDouble(text.trimmed(), &ok);
			if (!ok) {
				parsed = text.trimmed().toDouble(&ok);
			}
			if (ok) {
				*value = parsed;
			}
			return ok;
		}

		void handleItemChanged(QTreeWidgetItem *item, int column)
		{
			if (m_rebuilding || !item || column != 1) {
				return;
			}

			const EditProperty property = static_cast<EditProperty>(
					item->data(1, kPropertyRole).toInt());
			if (property == NoProperty) {
				return;
			}

			const int group_index = item->data(1, kGroupRole).toInt();
			if (group_index < 0 || group_index >= m_groups.size()) {
				rebuildTree();
				return;
			}

			if (item->text(1).trimmed() == mixedValue()) {
				return;
			}

			qreal value = 0.0;
			if (!parseNumber(item->text(1), &value)) {
				rebuildTree();
				return;
			}

			if (property == FontSize && value <= 0.0) {
				rebuildTree();
				return;
			}

			applyProperty(group_index, property, value);
		}

		void applyProperty(int group_index, EditProperty property, qreal value)
		{
			const QList<DynamicElementTextItem *> texts =
					m_groups.at(group_index).texts;
			if (texts.isEmpty() || !texts.first()->parentElement()
					|| !texts.first()->parentElement()->diagram())
			{
				rebuildTree();
				return;
			}

			Diagram *diagram = texts.first()->parentElement()->diagram();
			auto *macro = new QUndoCommand;

			QString property_name;
			switch (property)
			{
				case FontSize: property_name = tr("tamaño"); break;
				case TextWidth: property_name = tr("anchura"); break;
				case PositionX: property_name = tr("posición X"); break;
				case PositionY: property_name = tr("posición Y"); break;
				case Rotation: property_name = tr("rotación"); break;
				default: break;
			}
			macro->setText(
					tr("Modificar %1 en %2 textos")
							.arg(property_name)
							.arg(texts.size()));

			for (DynamicElementTextItem *text : texts)
			{
				QPropertyUndoCommand *command = nullptr;
				switch (property)
				{
					case FontSize:
					{
						QFont old_font = text->font();
						QFont new_font = old_font;
						new_font.setPointSize(qRound(value));
						if (new_font != old_font) {
							command = new QPropertyUndoCommand(
									text, "font", old_font, new_font, macro);
						}
						break;
					}
					case TextWidth:
						if (text->textWidth() != value) {
							command = new QPropertyUndoCommand(
									text,
									"textWidth",
									text->textWidth(),
									value,
									macro);
						}
						break;
					case PositionX:
					case PositionY:
					{
						if (text->parentGroup()) {
							break;
						}
						const QPointF old_pos = text->pos();
						QPointF new_pos = old_pos;
						if (property == PositionX) {
							new_pos.setX(value);
						} else {
							new_pos.setY(value);
						}
						if (new_pos != old_pos) {
							command = new QPropertyUndoCommand(
									text, "pos", old_pos, new_pos, macro);
						}
						break;
					}
					case Rotation:
						if (text->rotation() != value) {
							command = new QPropertyUndoCommand(
									text,
									"rotation",
									text->rotation(),
									value,
									macro);
						}
						break;
					default:
						break;
				}

				if (command
						&& (property == TextWidth
							|| property == PositionX
							|| property == PositionY
							|| property == Rotation))
				{
					command->setAnimated(true, false);
				}
			}

			if (macro->childCount() > 0) {
				diagram->undoStack().push(macro);
			} else {
				delete macro;
			}

			rebuildTree();
		}

	private:
		QLabel *m_summary = nullptr;
		QTabWidget *m_tabs = nullptr;
		QTreeWidget *m_tree = nullptr;
		QList<TextGroup> m_groups;
		int m_selection_count = 0;
		bool m_rebuilding = false;
};

} // namespace

/**
	@brief PropertiesEditorFactory::propertiesEditor
	@param model : the model to be edited
	@param editor :
	if the properties editor to be created is the same class as editor,
	the this function set item as edited item of editor and return editor
	@param parent : parent widget of the returned editor
	@return an editor or nullptr
*/
PropertiesEditorWidget *PropertiesEditorFactory::propertiesEditor(
		QAbstractItemModel *model,
		PropertiesEditorWidget *editor,
		QWidget *parent)
{
	if (auto m = static_cast<ProjectDBModel *>(model))
	{
		if (editor &&
			editor->metaObject()->className()
				== ProjectDBModelPropertiesWidget::staticMetaObject.className())
		{
			static_cast<ProjectDBModelPropertiesWidget *>(editor)->setModel(m);
			return editor;
		}
		return new ProjectDBModelPropertiesWidget(m, parent);
	}
	return nullptr;
}

/**
	@brief propertiesEditor
	@param items : The items to be edited
	@param editor :
	If the properties editor to be created is the same class as editor,
	then this function set item as edited item of editor and return editor
	@param parent : parent widget of the returned editor
	@return : an editor or nullptr;
*/
PropertiesEditorWidget *PropertiesEditorFactory::propertiesEditor(
		QList<QGraphicsItem *> items,
		PropertiesEditorWidget *editor,
		QWidget *parent)
{
	const int count_ = items.size();
	if (count_ == 0) {
		return nullptr;
	}
	QGraphicsItem *item = items.first();
	const int type_ = item->type();

		//The editor widget can only edit one item
		//or several items of the same type
	for (auto qgi : items) {
		if (qgi->type() != type_) {
			return nullptr;
		}
	}

	QString class_name;
	if (editor) {
		class_name = editor->metaObject()->className();
	}

	switch (type_)
	{
		case Element::Type: //1000
		{
			if (count_ > 1)
			{
				QList<Element *> elements;
				for (QGraphicsItem *qgi : items) {
					elements << static_cast<Element *>(qgi);
				}
				return new MultiDynamicTextPropertiesWidget(elements, parent);
			}

			auto elmt = static_cast<Element*>(item);
			//auto created_editor = new ElementPropertiesWidget(elmt, parent);

				//We already edit an element, just update the editor with a new element
			if (class_name == ElementPropertiesWidget::staticMetaObject.className())
			{
				static_cast<ElementPropertiesWidget*>(editor)->setElement(elmt);
				return  editor;
			}
			return  new ElementPropertiesWidget(elmt, parent);
		}
		case IndependentTextItem::Type: //1005
		{
			QList<IndependentTextItem *> text_list;
			for (QGraphicsItem *qgi : items) {
				text_list.append(static_cast<IndependentTextItem*>(qgi));
			}

			if (class_name == IndiTextPropertiesWidget::staticMetaObject.className())
			{
				static_cast<IndiTextPropertiesWidget*>(editor)->setText(text_list);
				return  editor;
			}

			return new IndiTextPropertiesWidget(text_list, parent);
		}
		case DiagramImageItem::Type: //1007
		{
			if (count_ > 1) {
				return nullptr;
			}
			return new ImagePropertiesWidget(static_cast<DiagramImageItem*>(item), parent);
		}
		case QetShapeItem::Type: //1008
		{
			QList<QetShapeItem *> shapes_list;
			for (QGraphicsItem *qgi : items) {
				shapes_list.append(static_cast<QetShapeItem*>(qgi));
			}

			if (class_name == ShapeGraphicsItemPropertiesWidget::staticMetaObject.className())
			{
				static_cast<ShapeGraphicsItemPropertiesWidget*>(editor)->setItems(shapes_list);
				return editor;
			}

			return new ShapeGraphicsItemPropertiesWidget(shapes_list, parent);
		}
		case DynamicElementTextItem::Type: //1010
		{
			if (count_ > 1)
			{
				QList<DynamicElementTextItem *> texts;
				for (QGraphicsItem *qgi : items) {
					texts << static_cast<DynamicElementTextItem *>(qgi);
				}
				return new MultiDynamicTextPropertiesWidget(texts, parent);
			}

			DynamicElementTextItem *deti = static_cast<DynamicElementTextItem *>(item);
				//For dynamic element text, we open the element editor to edit it
				//If we already edit an element, just update the editor with a new element
			if (class_name == ElementPropertiesWidget::staticMetaObject.className())
			{
				static_cast<ElementPropertiesWidget*>(editor)->setDynamicText(deti);
				return editor;
			}
			return new ElementPropertiesWidget(deti, parent);
		}
		case QGraphicsItemGroup::Type:
		{
			if (count_ > 1) {
				return nullptr;
			}

			if(ElementTextItemGroup *group = dynamic_cast<ElementTextItemGroup *>(item))
			{
					//For element text item group, we open the element editor to edit it
					//If we already edit an element, just update the editor with a new element
				if(class_name == ElementPropertiesWidget::staticMetaObject.className())
				{
					static_cast<ElementPropertiesWidget *>(editor)->setTextsGroup(group);
					return editor;
				}
				return new ElementPropertiesWidget(group, parent);
			}
			break;
		}
		case QetGraphicsTableItem::Type:
		{
			if (count_ > 1) {
				return nullptr;
			}

			auto table = static_cast<QetGraphicsTableItem*>(item);
			if (class_name == GraphicsTablePropertiesEditor::staticMetaObject.className())
			{
				static_cast<GraphicsTablePropertiesEditor*>(editor)->setTable(table);
				return editor;
			}
			return new GraphicsTablePropertiesEditor(table, parent);
		}
		default:
			return nullptr;
	}

	return nullptr;
}
