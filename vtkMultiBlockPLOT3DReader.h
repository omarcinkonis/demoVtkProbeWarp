 /*=========================================================================
  
   Program:   Visualization Toolkit
   Module:    vtkMultiBlockPLOT3DReader.h
  
   Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
   All rights reserved.
   See Copyright.txt or http://www.kitware.com/Copyright.htm for details.
  
      This software is distributed WITHOUT ANY WARRANTY; without even
      the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
      PURPOSE.  See the above copyright notice for more information.
  
 =========================================================================*/
 #ifndef vtkMultiBlockPLOT3DReader_h
 #define vtkMultiBlockPLOT3DReader_h
  
 #include "vtkIOParallelModule.h" // For export macro
 #include "vtkParallelReader.h"
 #include <vector> // For holding function-names
  
 class vtkDataArray;
 class vtkDataSetAttributes;
 class vtkIntArray;
 class vtkMultiBlockPLOT3DReaderRecord;
 class vtkMultiProcessController;
 class vtkStructuredGrid;
 class vtkUnsignedCharArray;
 struct vtkMultiBlockPLOT3DReaderInternals;
 class vtkMultiBlockDataSet;
  
 namespace Functors
 {
 class ComputeFunctor;
 class ComputeTemperatureFunctor;
 class ComputePressureFunctor;
 class ComputePressureCoefficientFunctor;
 class ComputeMachNumberFunctor;
 class ComputeSoundSpeedFunctor;
 class ComputeEnthalpyFunctor;
 class ComputeKinecticEnergyFunctor;
 class ComputeVelocityMagnitudeFunctor;
 class ComputeEntropyFunctor;
 class ComputeSwirlFunctor;
 class ComputeVelocityFunctor;
 class ComputeVorticityMagnitudeFunctor;
 class ComputePressureGradientFunctor;
 class ComputeVorticityFunctor;
 class ComputeStrainRateFunctor;
 }
  
 class VTKIOPARALLEL_EXPORT vtkMultiBlockPLOT3DReader : public vtkParallelReader
 {
   friend class Functors::ComputeFunctor;
   friend class Functors::ComputeTemperatureFunctor;
   friend class Functors::ComputePressureFunctor;
   friend class Functors::ComputePressureCoefficientFunctor;
   friend class Functors::ComputeMachNumberFunctor;
   friend class Functors::ComputeSoundSpeedFunctor;
   friend class Functors::ComputeEnthalpyFunctor;
   friend class Functors::ComputeKinecticEnergyFunctor;
   friend class Functors::ComputeVelocityMagnitudeFunctor;
   friend class Functors::ComputeEntropyFunctor;
   friend class Functors::ComputeSwirlFunctor;
   friend class Functors::ComputeVelocityFunctor;
   friend class Functors::ComputeVorticityMagnitudeFunctor;
   friend class Functors::ComputePressureGradientFunctor;
   friend class Functors::ComputeVorticityFunctor;
   friend class Functors::ComputeStrainRateFunctor;
  
 public:
   static vtkMultiBlockPLOT3DReader* New();
   vtkTypeMacro(vtkMultiBlockPLOT3DReader, vtkParallelReader);
   void PrintSelf(ostream& os, vtkIndent indent) override;
  
  
   vtkMultiBlockDataSet* GetOutput();
   vtkMultiBlockDataSet* GetOutput(int);
  
  
   void SetFileName(const char* name) { this->SetXYZFileName(name); }
   const char* GetFileName() { return this->GetXYZFileName(); }
   const char* GetFileName(int i) { return this->vtkParallelReader::GetFileName(i); }
   virtual void SetXYZFileName(const char*);
   vtkGetStringMacro(XYZFileName);
  
  
   void SetQFileName(const char* name);
   const char* GetQFileName();
  
  
   vtkSetStringMacro(FunctionFileName);
   vtkGetStringMacro(FunctionFileName);
  
  
   vtkSetMacro(AutoDetectFormat, vtkTypeBool);
   vtkGetMacro(AutoDetectFormat, vtkTypeBool);
   vtkBooleanMacro(AutoDetectFormat, vtkTypeBool);
  
  
   vtkSetMacro(BinaryFile, vtkTypeBool);
   vtkGetMacro(BinaryFile, vtkTypeBool);
   vtkBooleanMacro(BinaryFile, vtkTypeBool);
  
  
   vtkSetMacro(MultiGrid, vtkTypeBool);
   vtkGetMacro(MultiGrid, vtkTypeBool);
   vtkBooleanMacro(MultiGrid, vtkTypeBool);
  
  
   vtkSetMacro(HasByteCount, vtkTypeBool);
   vtkGetMacro(HasByteCount, vtkTypeBool);
   vtkBooleanMacro(HasByteCount, vtkTypeBool);
  
  
   vtkSetMacro(IBlanking, vtkTypeBool);
   vtkGetMacro(IBlanking, vtkTypeBool);
   vtkBooleanMacro(IBlanking, vtkTypeBool);
  
  
   vtkSetMacro(TwoDimensionalGeometry, vtkTypeBool);
   vtkGetMacro(TwoDimensionalGeometry, vtkTypeBool);
   vtkBooleanMacro(TwoDimensionalGeometry, vtkTypeBool);
  
  
   vtkSetMacro(DoublePrecision, vtkTypeBool);
   vtkGetMacro(DoublePrecision, vtkTypeBool);
   vtkBooleanMacro(DoublePrecision, vtkTypeBool);
  
  
   vtkSetMacro(ForceRead, vtkTypeBool);
   vtkGetMacro(ForceRead, vtkTypeBool);
   vtkBooleanMacro(ForceRead, vtkTypeBool);
  
  
   void SetByteOrderToBigEndian();
   void SetByteOrderToLittleEndian();
   vtkSetMacro(ByteOrder, int);
   vtkGetMacro(ByteOrder, int);
   const char* GetByteOrderAsString();
  
  
   vtkSetMacro(R, double);
   vtkGetMacro(R, double);
  
  
   vtkSetMacro(Gamma, double);
   vtkGetMacro(Gamma, double);
  
  
   vtkSetMacro(PreserveIntermediateFunctions, bool);
   vtkGetMacro(PreserveIntermediateFunctions, bool);
   vtkBooleanMacro(PreserveIntermediateFunctions, bool);
  
  
   void SetScalarFunctionNumber(int num);
   vtkGetMacro(ScalarFunctionNumber, int);
  
  
   void SetVectorFunctionNumber(int num);
   vtkGetMacro(VectorFunctionNumber, int);
  
  
   void AddFunction(int functionNumber);
   void RemoveFunction(int);
   void RemoveAllFunctions();
  
   virtual int CanReadBinaryFile(const char* fname);
  
  
   void SetController(vtkMultiProcessController* c);
   vtkGetObjectMacro(Controller, vtkMultiProcessController);
  
   void AddFunctionName(const std::string& name) { FunctionNames.push_back(name); }
  
   enum
   {
     FILE_BIG_ENDIAN = 0,
     FILE_LITTLE_ENDIAN = 1
   };
  
  
   int ReadMetaData(vtkInformation* metadata) override;
   int ReadMesh(int piece, int npieces, int nghosts, int timestep, vtkDataObject* output) override;
   int ReadPoints(int piece, int npieces, int nghosts, int timestep, vtkDataObject* output) override;
   int ReadArrays(int piece, int npieces, int nghosts, int timestep, vtkDataObject* output) override;
  
 protected:
   vtkMultiBlockPLOT3DReader();
   ~vtkMultiBlockPLOT3DReader() override;
  
  
   double GetTimeValue(const std::string& fname) override;
   int ReadMesh(
     const std::string& fname, int piece, int npieces, int nghosts, vtkDataObject* output) override;
   int ReadPoints(
     const std::string& fname, int piece, int npieces, int nghosts, vtkDataObject* output) override;
   int ReadArrays(
     const std::string& fname, int piece, int npieces, int nghosts, vtkDataObject* output) override;
  
   vtkDataArray* CreateFloatArray();
  
   int CheckFile(FILE*& fp, const char* fname);
   int CheckGeometryFile(FILE*& xyzFp);
   int CheckFunctionFile(FILE*& fFp);
  
   int GetByteCountSize();
   int SkipByteCount(FILE* fp);
   int ReadIntBlock(FILE* fp, int n, int* block);
  
   vtkIdType ReadValues(FILE* fp, int n, vtkDataArray* scalar);
   virtual int ReadIntScalar(void* vfp, int extent[6], int wextent[6], vtkDataArray* scalar,
     vtkTypeUInt64 offset, const vtkMultiBlockPLOT3DReaderRecord& currentRecord);
   virtual int ReadScalar(void* vfp, int extent[6], int wextent[6], vtkDataArray* scalar,
     vtkTypeUInt64 offset, const vtkMultiBlockPLOT3DReaderRecord& currentRecord);
   virtual int ReadVector(void* vfp, int extent[6], int wextent[6], int numDims,
     vtkDataArray* vector, vtkTypeUInt64 offset,
     const vtkMultiBlockPLOT3DReaderRecord& currentRecord);
   virtual int OpenFileForDataRead(void*& fp, const char* fname);
   virtual void CloseFile(void* fp);
  
   int GetNumberOfBlocksInternal(FILE* xyzFp, int allocate);
  
   int ReadGeometryHeader(FILE* fp);
   int ReadQHeader(FILE* fp, bool checkGrid, int& nq, int& nqc, int& overflow);
   int ReadFunctionHeader(FILE* fp, int* nFunctions);
  
   void CalculateFileSize(FILE* fp);
  
   int AutoDetectionCheck(FILE* fp);
  
   void AssignAttribute(int fNumber, vtkStructuredGrid* output, int attributeType);
   void MapFunction(int fNumber, vtkStructuredGrid* output);
  
  
   vtkDataArray* ComputeTemperature(vtkStructuredGrid* output);
   vtkDataArray* ComputePressure(vtkStructuredGrid* output);
   vtkDataArray* ComputeEnthalpy(vtkStructuredGrid* output);
   vtkDataArray* ComputeKineticEnergy(vtkStructuredGrid* output);
   vtkDataArray* ComputeVelocityMagnitude(vtkStructuredGrid* output);
   vtkDataArray* ComputeEntropy(vtkStructuredGrid* output);
   vtkDataArray* ComputeSwirl(vtkStructuredGrid* output);
   vtkDataArray* ComputeVelocity(vtkStructuredGrid* output);
   vtkDataArray* ComputeVorticity(vtkStructuredGrid* output);
   vtkDataArray* ComputePressureGradient(vtkStructuredGrid* output);
   vtkDataArray* ComputePressureCoefficient(vtkStructuredGrid* output);
   vtkDataArray* ComputeMachNumber(vtkStructuredGrid* output);
   vtkDataArray* ComputeSoundSpeed(vtkStructuredGrid* output);
   vtkDataArray* ComputeVorticityMagnitude(vtkStructuredGrid* output);
   vtkDataArray* ComputeStrainRate(vtkStructuredGrid* output);
  
   // Returns a vtkFloatArray or a vtkDoubleArray depending
   // on DoublePrecision setting
   vtkDataArray* NewFloatArray();
  
   // Delete references to any existing vtkPoints and
   // I-blank arrays. The next Update() will (re)read
   // the XYZ file.
   void ClearGeometryCache();
  
   double GetGamma(vtkIdType idx, vtkDataArray* gamma);
  
   int FillOutputPortInformation(int port, vtkInformation* info) override;
  
   // plot3d FileNames
   char* XYZFileName;
   char* QFileName;
   char* FunctionFileName;
   vtkTypeBool BinaryFile;
   vtkTypeBool HasByteCount;
   vtkTypeBool TwoDimensionalGeometry;
   vtkTypeBool MultiGrid;
   vtkTypeBool ForceRead;
   int ByteOrder;
   vtkTypeBool IBlanking;
   vtkTypeBool DoublePrecision;
   vtkTypeBool AutoDetectFormat;
  
   int ExecutedGhostLevels;
  
   size_t FileSize;
  
   // parameters used in computing derived functions
   double R;
   double Gamma;
   double GammaInf;
  
   bool PreserveIntermediateFunctions;
  
   // named functions from meta data
   std::vector<std::string> FunctionNames;
  
   // functions to read that are not scalars or vectors
   vtkIntArray* FunctionList;
  
   int ScalarFunctionNumber;
   int VectorFunctionNumber;
  
   vtkMultiBlockPLOT3DReaderInternals* Internal;
  
   vtkMultiProcessController* Controller;
  
 private:
   vtkMultiBlockPLOT3DReader(const vtkMultiBlockPLOT3DReader&) = delete;
   void operator=(const vtkMultiBlockPLOT3DReader&) = delete;
  
   // Key used to flag intermediate results.
   static vtkInformationIntegerKey* INTERMEDIATE_RESULT();
  
   void RemoveIntermediateFunctions(vtkDataSetAttributes* dsa);
 };
  
 #endif