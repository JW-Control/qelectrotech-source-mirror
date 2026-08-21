# Copyright 2006 The QElectroTech Team
# This file is part of QElectroTech.
#
# QElectroTech is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
#
# QElectroTech is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with QElectroTech. If not, see <http://www.gnu.org/licenses/>.

message(" - git_last_commit_sha")

find_package(Git QUIET)

if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
  #get GIT COMMIT SHA
  execute_process(
    COMMAND ${GIT_EXECUTABLE} -C ${QET_DIR} rev-parse --verify HEAD
    OUTPUT_VARIABLE  GIT_COMMIT_SHA
    RESULT_VARIABLE GIT_COMMIT_RESULT)

  # This strips terminating newline in the variable
  string(REGEX REPLACE "\n$" "" GIT_COMMIT_SHA "${GIT_COMMIT_SHA}")

  if(NOT GIT_COMMIT_RESULT EQUAL "0")
    message(
      FATAL_ERROR
      "git rev-parse --verify HEAD failed with "
      ${GIT_COMMIT_RESULT}
      ", please check")
  endif()
endif()

# GIT_COMMIT_SHA is consumed only by sources/machine_info.cpp. Keeping it as
# a directory-wide -D made every Git commit invalidate every C++ object, which
# defeated the incremental JW-QET launcher and forced ~470 recompilations.
# Scope the definition to the one source that needs it so future commits only
# rebuild machine_info.cpp plus the final link step.
set_source_files_properties(
  "${QET_DIR}/sources/machine_info.cpp"
  PROPERTIES
  COMPILE_DEFINITIONS "GIT_COMMIT_SHA=\"${GIT_COMMIT_SHA}\""
)
