#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkContourFilter.h>
#include <vtkGenericOutlineFilter.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPointSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <vtkStreamTracer.h>
#include <vtkTubeFilter.h>
#include <vtkUnstructuredGrid.h>
#include <vtkVRMLImporter.h>
#include <vtkUnstructuredGridReader.h>
#include <vtkPlane.h>
#include <vtkProbeFilter.h>
#include <vtkCutter.h>
#include <vtkWarpScalar.h>
#include <vtkDataSetMapper.h>
#include <vtkPointData.h>

int main()
{
  vtkNew<vtkNamedColors> colors;
  vtkColor3d isoSurfaceColor = colors->GetColor3d("WhiteSmoke");
  vtkColor3d backgroundColor = colors->GetColor3d("SlateGray");

  vtkNew<vtkRenderer> renderer;
  renderer->UseHiddenLineRemovalOn();

  vtkNew<vtkRenderWindow> renderWindow;
  renderWindow->AddRenderer(renderer);

  vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Import the VRML Files that define the geometry
  vtkNew<vtkVRMLImporter> importer;
  importer->SetRenderWindow(renderWindow);
  importer->SetFileName("../data/fire_geometry.wrl");
  importer->Update();

  // Read the UnstructuredGrid and define the reader
  vtkNew<vtkUnstructuredGridReader> reader;
  reader->SetFileName("../data/fire.vtk");
  reader->Update();

  // Create an Isosurface
  vtkNew<vtkContourFilter> isoSurface;
  isoSurface->SetValue(0, 550.0);
  isoSurface->SetInputConnection(reader->GetOutputPort());

  vtkNew<vtkPolyDataMapper> isoSurfaceMapper;
  isoSurfaceMapper->SetInputConnection(isoSurface->GetOutputPort());
  isoSurfaceMapper->ScalarVisibilityOff();

  vtkNew<vtkActor> isoSurfaceActor;
  isoSurfaceActor->SetMapper(isoSurfaceMapper);
  isoSurfaceActor->GetProperty()->SetOpacity(.5);
  isoSurfaceActor->GetProperty()->SetDiffuseColor(isoSurfaceColor.GetData());

  vtkNew<vtkPlane> plane;
  plane->SetOrigin(isoSurfaceActor->GetCenter());
  plane->SetNormal(1.0, 0.0, 0.0);

  vtkNew<vtkCutter> cutter;
  cutter->SetCutFunction(plane);
  cutter->SetInputConnection(reader->GetOutputPort());
  cutter->Update();

  vtkNew<vtkPolyDataMapper> cutterMapper;
  cutterMapper->SetInputConnection(cutter->GetOutputPort());
  cutterMapper->ScalarVisibilityOff();

  vtkNew<vtkActor> cutterActor;
  cutterActor->SetMapper(cutterMapper);
  cutterActor->GetProperty()->SetRepresentationToWireframe();

  vtkNew<vtkProbeFilter> probe;
  probe->SetInputConnection(cutter->GetOutputPort());
  probe->SetSourceConnection(reader->GetOutputPort());
  probe->Update();

  vtkNew<vtkWarpScalar> warp;
  warp->SetInputConnection(probe->GetOutputPort());
  warp->SetScaleFactor(0.002);
  warp->SetNormal(1.0, 0.0, 0.0);
  warp->Update();

  vtkNew<vtkPolyDataMapper> warpMapper;
  warpMapper->SetInputConnection(warp->GetOutputPort());
  warpMapper->SetScalarModeToUsePointFieldData();
  warpMapper->SelectColorArray("t");
  warpMapper->SetScalarRange(reader->GetOutput()->GetPointData()->GetArray("t")->GetRange(0));
  
  vtkNew<vtkActor> warpActor;
  warpActor->SetMapper(warpMapper);

  //

  renderer->AddActor(cutterActor);
  renderer->AddActor(warpActor);
  renderer->AddActor(isoSurfaceActor);

  renderer->SetBackground(backgroundColor.GetData());
  renderWindow->SetSize(1920, 1080);
  renderWindow->SetWindowName("Marcinkonis_MKDfs-18");
  renderWindow->Render();

  renderer->GetActiveCamera()->Azimuth(20.0);
  renderer->GetActiveCamera()->Elevation(10.0);
  renderer->GetActiveCamera()->Dolly(1.25);
  renderer->ResetCameraClippingRange();

  renderWindow->Render();

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}