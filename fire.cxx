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
#include <vtkDelaunay2D.h>
#include <vtkDataSetMapper.h>

int main()
{
  vtkNew<vtkNamedColors> colors;
  vtkColor3d isoSurfaceColor = colors->GetColor3d("WhiteSmoke");
  // vtkColor3d sphereColor = colors->GetColor3d("hotpink");
  vtkColor3d planeColor = colors->GetColor3d("hotpink");
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
  importer->SetFileName("D:\\VTK\\Projects\\source\\Marcinkonis_MKDFs-18\\fire_geometry.wrl");
  importer->Update();

  // Read the UnstructuredGrid and define the reader
  vtkNew<vtkUnstructuredGridReader> reader;
  reader->SetFileName("D:\\VTK\\Projects\\source\\Marcinkonis_MKDFs-18\\fire.vtk");
  reader->Update();

  // Create an outline
  //vtkNew<vtkGenericOutlineFilter> outline;
  //outline->SetInputConnection(reader->GetOutputPort());

  //// Create Seeds
  //vtkNew<vtkPointSource> seeds;
  //seeds->SetRadius(0.2);
  //seeds->SetCenter(3.5, 0.625, 1.25);
  //seeds->SetNumberOfPoints(50);

  //// Create streamlines
  //vtkNew<vtkStreamTracer> streamTracer;
  //streamTracer->SetIntegrationDirectionToBoth();
  //streamTracer->SetInputConnection(solution->GetOutputPort());
  //streamTracer->SetSourceConnection(seeds->GetOutputPort());
  //streamTracer->SetMaximumPropagation(50);
  //streamTracer->SetInitialIntegrationStep(.2);
  //streamTracer->SetMinimumIntegrationStep(.01);
  //streamTracer->SetIntegratorType(1);
  //streamTracer->SetComputeVorticity(1);

  //vtkNew<vtkTubeFilter> tubes;
  //tubes->SetInputConnection(streamTracer->GetOutputPort());
  //tubes->SetNumberOfSides(8);
  //tubes->SetRadius(.02);
  //tubes->SetVaryRadius(0);

  //vtkNew<vtkPolyDataMapper> mapTubes;
  //mapTubes->SetInputConnection(tubes->GetOutputPort());
  //mapTubes->SetScalarRange(solution->GetOutput()->GetScalarRange());

  //vtkNew<vtkActor> tubesActor;
  //tubesActor->SetMapper(mapTubes);

  // Create probePolyData
  vtkNew<vtkPolyData> probePolyData;
  //probePolyData->SetPoints(reader->GetOutputPort());

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
  plane->SetNormal((1, 0, 0) + isoSurfaceActor->GetCenter());
  //vtkNew<vtkPolyDataMapper> planeMapper;
  //planeMapper->SetInputConnection(planeSource->GetOutputPort());

  //vtkNew<vtkActor> planeActor;
  //planeActor->SetMapper(planeMapper);
  //planeActor->GetProperty()->SetOpacity(1.0);
  //planeActor->GetProperty()->SetSpecular(.4);
  //planeActor->GetProperty()->SetSpecularPower(80);
  //planeActor->GetProperty()->SetDiffuseColor(planeColor.GetData());

  vtkNew<vtkCutter> cutter;
  cutter->SetCutFunction(plane);
  cutter->SetInputConnection(reader->GetOutputPort());
  cutter->Update();

  vtkNew<vtkProbeFilter> probe;
  probe->SetInputConnection(cutter->GetOutputPort());
  probe->SetSourceConnection(reader->GetOutputPort());
  probe->Update();

  vtkNew<vtkWarpScalar> gridWarpScalar;
  gridWarpScalar->SetInputConnection(probe->GetOutputPort());
  gridWarpScalar->Update();

  // Mesh the output grid points
  vtkNew<vtkDelaunay2D> gridDelaunay;
  gridDelaunay->SetInputConnection(gridWarpScalar->GetOutputPort());

  vtkNew<vtkDataSetMapper> gridMapper;
  gridMapper->SetInputConnection(gridDelaunay->GetOutputPort());
  gridMapper->ScalarVisibilityOff();

  vtkNew<vtkActor> gridActor;
  gridActor->SetMapper(gridMapper);
  gridActor->GetProperty()->SetColor(colors->GetColor3d("SteelBlue").GetData());
  gridActor->GetProperty()->SetPointSize(3);

  //

  //vtkNew<vtkSphereSource> sphere;
  //sphere->SetCenter(seeds->GetCenter());
  //sphere->SetRadius(seeds->GetRadius());
  //sphere->SetThetaResolution(20);
  //sphere->SetPhiResolution(11);
  //vtkNew<vtkPolyDataMapper> sphereMapper;
  //sphereMapper->SetInputConnection(sphere->GetOutputPort());

  //vtkNew<vtkActor> sphereActor;
  //sphereActor->SetMapper(sphereMapper);
  //sphereActor->GetProperty()->SetOpacity(1.0);
  //sphereActor->GetProperty()->SetSpecular(.4);
  //sphereActor->GetProperty()->SetSpecularPower(80);
  //sphereActor->GetProperty()->SetDiffuseColor(sphereColor.GetData());

  //renderer->AddActor(tubesActor);
  //renderer->AddActor(sphereActor);
  //renderer->AddActor(planeActor);
  renderer->AddActor(gridActor);
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