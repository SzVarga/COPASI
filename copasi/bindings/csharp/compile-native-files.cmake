# Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the 
# University of Virginia, University of Heidelberg, and University 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and University of 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Copyright (C) 2012 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 







###############################################################################
#
# Description       : CMake build script for native C# library
# Original author(s): Frank Bergmann <fbergman@caltech.edu>
# Organization      : California Institute of Technology
#
# This file is part of libSBML.  Please visit http://sbml.org for more
# information about SBML, and the latest version of libSBML.
#
# Copyright (C) 2009-2012 jointly by the following organizations: 
#     1. California Institute of Technology, Pasadena, CA, USA
#     2. EMBL European Bioinformatics Institute (EBML-EBI), Hinxton, UK
#  
# Copyright (C) 2006-2008 by the California Institute of Technology,
#     Pasadena, CA, USA 
#  
# Copyright (C) 2002-2005 jointly by the following organizations: 
#     1. California Institute of Technology, Pasadena, CA, USA
#     2. Japan Science and Technology Agency, Japan
# 
# This library is free software; you can redistribute it and/or modify it
# under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation.  A copy of the license agreement is provided
# in the file named "LICENSE.txt" included with this software distribution
# and also available online as http://sbml.org/software/libsbml/license.html
#
###############################################################################

message("Creating: copasicsP.dll")

# find all sources
file(GLOB_RECURSE SOURCE_FILES RELATIVE ${BIN_DIRECTORY} ${BIN_DIRECTORY}/csharp-files/*.cs)
set(SOURCE_FILES ${SOURCE_FILES} ${BIN_DIRECTORY}/AssemblyInfo.cs)

SET(PATCH_SWIG_FILES ON)

####################################################################
#
# Fix swig enum code
# 
# Add broken swig generated files below
#

set (SWIG_ENUM_FIX_FILES 
        "${CMAKE_CURRENT_BINARY_DIR}/csharp-files/CTaskEnum.cs"
        "${CMAKE_CURRENT_BINARY_DIR}/csharp-files/CModelEntity.cs"
        "${CMAKE_CURRENT_BINARY_DIR}/csharp-files/CDataArray.cs"
        "${CMAKE_CURRENT_BINARY_DIR}/csharp-files/CCore.cs"
        "${CMAKE_CURRENT_BINARY_DIR}/csharp-files/CModelParameter.cs"
        "${CMAKE_CURRENT_BINARY_DIR}/csharp-files/CFunctionParameter.cs"
        "${CMAKE_CURRENT_BINARY_DIR}/csharp-files/CCopasiParameter.cs"
        "${CMAKE_CURRENT_BINARY_DIR}/csharp-files/CReaction.cs"
        "${CMAKE_CURRENT_BINARY_DIR}/csharp-files/CModel.cs"
        "${CMAKE_CURRENT_BINARY_DIR}/csharp-files/CUndoData.cs"
        "${CMAKE_CURRENT_BINARY_DIR}/csharp-files/CNewtonMethod.cs"
        "${CMAKE_CURRENT_BINARY_DIR}/csharp-files/CCopasiTimer.cs"
        "${CMAKE_CURRENT_BINARY_DIR}/csharp-files/CDataModel.cs"
        "${CMAKE_CURRENT_BINARY_DIR}/csharp-files/CPlotItem.cs"
    )


# convert paths
set(NATIVE_FILES)
foreach(csFile ${SOURCE_FILES})
	file(TO_NATIVE_PATH ${csFile} temp)
	set(NATIVE_FILES ${NATIVE_FILES} ${temp})
  
  if (PATCH_SWIG_FILES)
  
    # read file, prepend using statement, write again ... 
    file(READ ${csFile} content)
    file(WRITE ${csFile} "using System;\nusing System.Runtime.InteropServices;\n\n${content}")

  endif(PATCH_SWIG_FILES)

  
endforeach()


foreach(broken_file ${SWIG_ENUM_FIX_FILES})
  file(READ "${broken_file}" SOURCECODE)
  string(REGEX REPLACE 
   "public const int ([a-zA-Z]*_)([_a-zA-Z0-9]*) = ([a-zA-Z0-9]*) \\+ 1"
   "public const int \\1\\2 = \\1\\3 + 1; // FIXED" 
   SOURCECODE "${SOURCECODE}")
  file(WRITE "${broken_file}" "${SOURCECODE}")
  get_filename_component(baseName ${broken_file} NAME)
  message (STATUS "Patched ${baseName}")
endforeach()


# delete file if it exists
if (EXISTS ${BIN_DIRECTORY}/copasicsP.dll)
	file(REMOVE ${BIN_DIRECTORY}/copasicsP.dll)	
endif()

# the compile run disables the following warnings
# -  105: duplicated using statement, due to the patch above 
# -  108: 'method name' hides inherited member 'base member name'. Use the 
#         new keyword if hiding was intended.
# -  114: 'method name' hides inherited member 'base member name'. To make 
#         the current member override that implementation, add the override 
#         keyword. Otherwise add the new keyword.
# - 1570: XML comment on 'class name' has badly formed XML.
# - 1572: XML comment on 'method name' has a param tag for 'parameter name'
#         but there is no parameter by that name.
# - 1573: Parameter 'parameter name' has no matching param tag in the XML 
#         comment for 'method name' (but other parameters do).
# - 1574: XML comment on 'method name' has cref attribute 'method name' 
#         that could not be resolved.
# - 1591: Missing XML comment for publicly visible type or member 'method
#         name'

# compile files


execute_process(
	COMMAND "${CSHARP_COMPILER}"
		 -target:library
		 -nowarn:105,108,109,114,1570,1572,1573,1574,1591
		 -out:copasicsP.dll
		 ${CSHARP_EXTRA_ARGS}
		 ${NATIVE_FILES}
	
	WORKING_DIRECTORY "${BIN_DIRECTORY}"
)

if (EXISTS ${BIN_DIRECTORY}/copasicsP.dll)
  if (EXISTS ${BIN_DIRECTORY}/examples/copasicsP.dll)
	  file(REMOVE ${BIN_DIRECTORY}/examples/copasicsP.dll)	
  endif()
	file(COPY ${BIN_DIRECTORY}/copasicsP.dll DESTINATION ${BIN_DIRECTORY}/examples/)
endif()

# # print variables for debug purposes
# message("BIN_DIRECTORY     : ${BIN_DIRECTORY}")
# message("SRC_DIRECTORY     : ${SRC_DIRECTORY}")
# message("CSHARP_COMPILER   : ${CSHARP_COMPILER}")
# message("CSHARP_EXTRA_ARGS : ${CSHARP_EXTRA_ARGS}")
# 

