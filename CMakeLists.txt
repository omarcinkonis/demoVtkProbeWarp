cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

project(Marcinkonis_MKDFs-18)

find_package(VTK COMPONENTS 
  vtkCommonColor
  vtkCommonCore
  vtkCommonDataModel
  vtkFiltersCore
  vtkFiltersFlowPaths
  vtkFiltersGeneric
  vtkFiltersSources
  vtkIOImport
  vtkIOLegacy
  vtkInteractionStyle
  vtkRenderingContextOpenGL2
  vtkRenderingCore
  vtkRenderingFreeType
  vtkRenderingGL2PSOpenGL2
  vtkRenderingOpenGL2
  QUIET
)

if (NOT VTK_FOUND)
  message("Skipping FireFlow: ${VTK_NOT_FOUND_MESSAGE}")
  return ()
endif()

# old system
include(${VTK_USE_FILE})
add_executable(fire fire.cxx)
target_link_libraries (fire ${VTK_LIBRARIES})