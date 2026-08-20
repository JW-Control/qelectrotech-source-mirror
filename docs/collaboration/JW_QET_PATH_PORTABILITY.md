# JW QET - Portabilidad de rutas del workspace colaborativo

Fecha: 2026-08-20

## Problema validado

Google Drive puede montar `Mi unidad` con letras distintas en cada PC.

Ejemplo real de validacion:

```text
PC1 -> H:\Mi unidad\...\JW_QET_COLLAB
PC2 -> G:\Mi unidad\...\JW_QET_COLLAB
```

Ambas rutas representan el mismo workspace sincronizado, pero una ruta absoluta guardada por PC2 no existe necesariamente en PC1.

## Regla

La letra de unidad y el prefijo local del workspace NO forman parte de la identidad colaborativa del proyecto.

Las rutas portables relevantes comienzan en una carpeta conocida del workspace:

```text
00_MASTER/
01_BASELINES/
02_WORKING/
03_INCOMING/
04_PUBLISHED/
05_ARCHIVE/
06_LOGS/
```

## Resolucion implementada

`tools/qet_collab_session.py` resuelve el workspace actual a partir de la ubicacion del manifiesto `.jwqet.json` dentro de `02_WORKING` o `03_INCOMING`.

Cuando consume una ruta creada en otra PC:

1. prioriza una ruta relativa del manifiesto si existe;
2. para manifiestos v1 con rutas absolutas, extrae el sufijo desde una carpeta conocida del workspace;
3. reconstruye la ruta usando el workspace visible en la PC actual;
4. solo usa la ruta absoluta original como fallback cuando sigue siendo valida.

Ejemplo:

```text
Manifiesto creado en PC2:
G:\Mi unidad\...\JW_QET_COLLAB\03_INCOMING\jeykco_pc2\Proyecto.qet

Consumido en PC1 como:
H:\Mi unidad\...\JW_QET_COLLAB\03_INCOMING\jeykco_pc2\Proyecto.qet
```

## Compatibilidad

El schema permanece en:

```text
jw-qet-collab-session.v1
```

Los manifiestos anteriores siguen siendo aceptados.

Los checkouts realizados mediante `tools/qet_collab_session.py` agregan tambien campos relativos (`*_relpath`) para nuevas sesiones. Los manifiestos generados por la UI actual de QET pueden seguir conteniendo rutas absolutas; la herramienta de submit/merge las rebasa automaticamente al workspace local.

## Criterio de prueba entre PCs

Antes de una ronda real, cada PC solo necesita verificar que su propia ruta local al mismo maestro exista:

```powershell
Test-Path "$WS\00_MASTER\Proyecto.qet"
```

No se requiere que `$WS` tenga la misma letra de unidad en las dos PCs.
