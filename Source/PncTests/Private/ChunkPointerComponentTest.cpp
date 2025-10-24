// Fill out your copyright notice in the Description page of Project Settings.


#include "ChunkPointerComponentTest.h"
#include "UE5PNC/public/PncDefault.h"


constexpr int kTestConstructingValue = 99;
constexpr int kTestWrintingValue = 50;
constexpr PNC::Size_t kTestNodeCapacity = 16;
constexpr PNC::Size_t kTestNodeCount0 = 0;
constexpr PNC::Size_t kTestNodeCount = 8;
constexpr PNC::Size_t kTestChunkCapacity = 12;
constexpr PNC::Size_t kTestChunkCount0 = 0;
constexpr PNC::Size_t kTestChunkCount = 6;
constexpr PNC::Size_t kTest1 = 1;
constexpr PNC::Size_t kTest0 = 0;

struct TypeCallCounter
{
public:
    std::atomic<PNC::Size_t> Ctor = 0;
    std::atomic<PNC::Size_t> Dtor = 0;
    std::atomic<PNC::Size_t> CopyCtor = 0;
    std::atomic<PNC::Size_t> MoveCtor = 0;
    std::atomic<PNC::Size_t> CopyAssign = 0;
    std::atomic<PNC::Size_t> MoveAssign = 0;
    void Reset()
    {
        Ctor = 0;
        Dtor = 0;
        CopyCtor = 0;
        MoveCtor = 0;
        CopyAssign = 0;
        MoveAssign = 0;
    }
};
struct CallCounter
{
public:
    static CallCounter Instance;
    TypeCallCounter B;
    TypeCallCounter W;

    void Reset()
    {
        B.Reset();
        W.Reset();
    }
};

CallCounter CallCounter::Instance;
void ResetCallCounter()
{
    CallCounter::Instance.Reset();
}
struct TestNodeComponentA : PNC::NodeComponent
{
public:
    int Value;
};
struct TestNodeComponentB : PNC::NodeComponent
{
public:
    int Value;
    TestNodeComponentB()
        :Value(kTestConstructingValue)
    {
        ++CallCounter::Instance.B.Ctor;
    }
    TestNodeComponentB(const TestNodeComponentB& o)
        :Value(o.Value)
    {
        ++CallCounter::Instance.B.CopyCtor;
    }
    TestNodeComponentB& operator=(const TestNodeComponentB& o)
    {
        Value = o.Value;
        ++CallCounter::Instance.B.CopyAssign;
        return *this;
    }
    TestNodeComponentB(TestNodeComponentB&& o)
        :Value(std::move(o.Value))
    {
        ++CallCounter::Instance.B.MoveCtor;
    }
    TestNodeComponentB& operator=(TestNodeComponentB&& o)
    {
        Value = std::move(o.Value);
        ++CallCounter::Instance.B.MoveAssign;
        return *this;
    }
    ~TestNodeComponentB()
    {
        ++CallCounter::Instance.B.Dtor;
    }
};

struct TestChunkComponentV : PNC::ChunkComponent
{
public:
    int Value;
};
struct TestChunkComponentW : PNC::ChunkComponent
{
public:
    int Value;
    TestChunkComponentW()
        :Value(kTestConstructingValue)
    {
        ++CallCounter::Instance.W.Ctor;
    }
    TestChunkComponentW(const TestChunkComponentW& o)
        :Value(o.Value)
    {
        ++CallCounter::Instance.W.CopyCtor;
    }
    TestChunkComponentW& operator=(const TestChunkComponentW& o)
    {
        Value = o.Value;
        ++CallCounter::Instance.W.CopyAssign;
        return *this;
    }
    TestChunkComponentW(TestChunkComponentW&& o)
        :Value(std::move(o.Value))
    {
        ++CallCounter::Instance.W.MoveCtor;
    }
    TestChunkComponentW& operator=(TestChunkComponentW&& o)
    {
        Value = std::move(o.Value);
        ++CallCounter::Instance.W.MoveAssign;
        return *this;
    }
    ~TestChunkComponentW()
    {
        ++CallCounter::Instance.W.Dtor;
    }

};

struct PncTestData
{
public:

    using A = TestNodeComponentA;
    using B = TestNodeComponentB;
    using V = TestChunkComponentV;
    using W = TestChunkComponentW;
public:

    PNC::ComponentType ComponentTypeA;
    PNC::ComponentType ComponentTypeB;
    PNC::ComponentType ComponentTypeV;
    PNC::ComponentType ComponentTypeW;

    PNC::ChunkStructure StructureA;
    PNC::ChunkStructure StructureB;
    PNC::ChunkStructure StructureAB;
    PNC::ChunkStructure StructureV;
    PNC::ChunkStructure StructureW;
    PNC::ChunkStructure StructureVW;
    PNC::ChunkStructure StructureAV;
    PNC::ChunkStructure StructureBV;
    PNC::ChunkStructure StructureABV;
    PNC::ChunkStructure StructureAVW;
    PNC::ChunkStructure StructureBVW;
    PNC::ChunkStructure StructureABVW;

    PncTestData()
        : ComponentTypeA((A*)nullptr)
        , ComponentTypeB((B*)nullptr)
        , ComponentTypeV((V*)nullptr)
        , ComponentTypeW((W*)nullptr)
        , StructureA   (&ComponentTypeA)
        , StructureB   (&ComponentTypeB)
        , StructureAB  (&ComponentTypeA, &ComponentTypeB)
        , StructureV   (&ComponentTypeV)
        , StructureW   (&ComponentTypeW)
        , StructureVW  (&ComponentTypeV, &ComponentTypeW)
        , StructureAV  (&ComponentTypeA, &ComponentTypeV)
        , StructureBV  (&ComponentTypeB, &ComponentTypeV)
        , StructureABV (&ComponentTypeA, &ComponentTypeB, &ComponentTypeV)
        , StructureAVW (&ComponentTypeA, &ComponentTypeV, &ComponentTypeW)
        , StructureBVW (&ComponentTypeB, &ComponentTypeV, &ComponentTypeW)
        , StructureABVW(&ComponentTypeA, &ComponentTypeB, &ComponentTypeV, &ComponentTypeW)
    {
    }
    PncTestData(const PncTestData& o) = delete;
    PncTestData& operator=(const PncTestData& o) = delete;
    PncTestData(PncTestData&& o) = delete;
    PncTestData& operator=(PncTestData&& o) = delete;

};

struct PncTestFixture
{
public:

    using A = TestNodeComponentA;
    using B = TestNodeComponentB;
    using V = TestChunkComponentV;
    using W = TestChunkComponentW;

    std::size_t AllocationCountBefore;
    PncTestData* Data;
    bool Failed;

    PncTestFixture()
        : AllocationCountBefore(PNC::MemoryTracker<>::AllocationCount)
        , Data(new PncTestData())
        , Failed(false)
    {
        ResetCallCounter();
    }
    PncTestFixture(const PncTestFixture& o) = delete;
    PncTestFixture& operator=(const PncTestFixture& o) = delete;
    PncTestFixture(PncTestFixture&& o) = delete;
    PncTestFixture& operator=(PncTestFixture&& o) = delete;
    ~PncTestFixture()
    {
        ensureMsgf(Data == nullptr, TEXT("PncTestFixture::Finalize must be called before detroying the fixture."));
    }

    bool Finalize(FAutomationTestBase& test)
    {
        delete Data;
        Data = nullptr;
        if (!test.TestEqual(TEXT("Remaining allocations should be 0"), PNC::MemoryTracker<>::AllocationCount, AllocationCountBefore))
            return false;
        //if (PNC::MemoryTracker<>::AllocationCount != 0)
        //{
        //    UE_LOG(LogFunctionalTest, Log, TEXT("Remaining allocations (%d) should be 0;"), PNC::MemoryTracker<>::AllocationCount);
        //}
        return !Failed;
    }
};


struct PncTestFixtureChunk : public PncTestFixture
{
public:
    PNC::Chunk* Chunk;
    PncTestFixtureChunk()
        : Chunk(new PNC::Chunk(&Data->StructureA, kTestNodeCapacity, kTestNodeCount0))
    {
        ResetCallCounter();
    }
    PncTestFixtureChunk(const PNC::ChunkStructure* structure, const PNC::Size_t nodeCapacity, const PNC::Size_t nodeCount)
        : Chunk(new PNC::Chunk(structure, nodeCapacity, nodeCount))
    {
        ResetCallCounter();
    }
    ~PncTestFixtureChunk()
    {
        delete Chunk;
    }
};

using Data = PncTestData;
using Fix = PncTestFixture;
using FixChunk = PncTestFixtureChunk;

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Fixture_Data, "Pnc.0Fixture.Data", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Fixture_Data::RunTest(const FString& Parameters)
{
    Fix fix;
    UTEST_EQUAL(TEXT("StructureA Component Type A index"), fix.Data->StructureA.GetComponentTypeIndexInChunk(&fix.Data->ComponentTypeA), 0);
    UTEST_EQUAL(TEXT("StructureB Component Type B index"), fix.Data->StructureB.GetComponentTypeIndexInChunk(&fix.Data->ComponentTypeB), 0);
    UTEST_EQUAL(TEXT("StructureV Component Type V index"), fix.Data->StructureV.GetComponentTypeIndexInChunk(&fix.Data->ComponentTypeV), 0);
    
    UTEST_GREATER_EQUAL(TEXT("StructureAB Component Type A index"), fix.Data->StructureAB.GetComponentTypeIndexInChunk(&fix.Data->ComponentTypeA), 0);
    UTEST_GREATER_EQUAL(TEXT("StructureAB Component Type B index"), fix.Data->StructureAB.GetComponentTypeIndexInChunk(&fix.Data->ComponentTypeB), 0);

    UTEST_GREATER_EQUAL(TEXT("StructureVW Component Type V index"), fix.Data->StructureVW.GetComponentTypeIndexInChunk(&fix.Data->ComponentTypeV), 0);
    UTEST_GREATER_EQUAL(TEXT("StructureVW Component Type W index"), fix.Data->StructureVW.GetComponentTypeIndexInChunk(&fix.Data->ComponentTypeW), 0);

    UTEST_GREATER_EQUAL(TEXT("StructureAV Component Type A index"), fix.Data->StructureAV.GetComponentTypeIndexInChunk(&fix.Data->ComponentTypeA), 0);
    UTEST_GREATER_EQUAL(TEXT("StructureAV Component Type V index"), fix.Data->StructureAV.GetComponentTypeIndexInChunk(&fix.Data->ComponentTypeV), 0);

    UTEST_GREATER_EQUAL(TEXT("StructureBV Component Type B index"), fix.Data->StructureBV.GetComponentTypeIndexInChunk(&fix.Data->ComponentTypeB), 0);
    UTEST_GREATER_EQUAL(TEXT("StructureBV Component Type V index"), fix.Data->StructureBV.GetComponentTypeIndexInChunk(&fix.Data->ComponentTypeV), 0);

    UTEST_GREATER_EQUAL(TEXT("StructureABV Component Type A index"), fix.Data->StructureABV.GetComponentTypeIndexInChunk(&fix.Data->ComponentTypeA), 0);
    UTEST_GREATER_EQUAL(TEXT("StructureABV Component Type B index"), fix.Data->StructureABV.GetComponentTypeIndexInChunk(&fix.Data->ComponentTypeB), 0);
    UTEST_GREATER_EQUAL(TEXT("StructureABV Component Type V index"), fix.Data->StructureABV.GetComponentTypeIndexInChunk(&fix.Data->ComponentTypeV), 0);

    UTEST_GREATER_EQUAL(TEXT("StructureAVW Component Type A index"), fix.Data->StructureAVW.GetComponentTypeIndexInChunk(&fix.Data->ComponentTypeA), 0);
    UTEST_GREATER_EQUAL(TEXT("StructureAVW Component Type V index"), fix.Data->StructureAVW.GetComponentTypeIndexInChunk(&fix.Data->ComponentTypeV), 0);
    UTEST_GREATER_EQUAL(TEXT("StructureAVW Component Type W index"), fix.Data->StructureAVW.GetComponentTypeIndexInChunk(&fix.Data->ComponentTypeW), 0);

    UTEST_GREATER_EQUAL(TEXT("StructureBVW Component Type B index"), fix.Data->StructureBVW.GetComponentTypeIndexInChunk(&fix.Data->ComponentTypeB), 0);
    UTEST_GREATER_EQUAL(TEXT("StructureBVW Component Type V index"), fix.Data->StructureBVW.GetComponentTypeIndexInChunk(&fix.Data->ComponentTypeV), 0);
    UTEST_GREATER_EQUAL(TEXT("StructureBVW Component Type W index"), fix.Data->StructureBVW.GetComponentTypeIndexInChunk(&fix.Data->ComponentTypeW), 0);

    UTEST_GREATER_EQUAL(TEXT("StructureABVW Component Type A index"), fix.Data->StructureABVW.GetComponentTypeIndexInChunk(&fix.Data->ComponentTypeA), 0);
    UTEST_GREATER_EQUAL(TEXT("StructureABVW Component Type B index"), fix.Data->StructureABVW.GetComponentTypeIndexInChunk(&fix.Data->ComponentTypeB), 0);
    UTEST_GREATER_EQUAL(TEXT("StructureABVW Component Type V index"), fix.Data->StructureABVW.GetComponentTypeIndexInChunk(&fix.Data->ComponentTypeV), 0);
    UTEST_GREATER_EQUAL(TEXT("StructureABVW Component Type W index"), fix.Data->StructureABVW.GetComponentTypeIndexInChunk(&fix.Data->ComponentTypeW), 0);

    return fix.Finalize(*this);
}

#pragma region New
// TODO New NullChunk
IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Chunk_New_NodeComponentPod, "Pnc.1Chunk.0New.NodeComponentPod", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Chunk_New_NodeComponentPod::RunTest(const FString& Parameters)
{		
    Fix fix;
    auto* chunk = new PNC::Chunk(&fix.Data->StructureA, kTestNodeCapacity, kTestNodeCount);
    UTEST_TRUE(TEXT("Has Chunk"), !!chunk);
    UTEST_EQUAL(TEXT("Node Capacity"), chunk->GetNodeCapacity(), kTestNodeCapacity);
    UTEST_EQUAL(TEXT("Node Count"), chunk->GetNodeCount(), kTestNodeCount);

    auto* componentDataA = chunk->GetComponentData<Fix::A>();
    UTEST_TRUE(TEXT("Has Node Component A"), !!componentDataA);

    for (PNC::Size_t i = 0; i < kTestNodeCount; ++i)
        componentDataA[i].Value = kTestWrintingValue;

    for (PNC::Size_t i = 0; i < kTestNodeCount; ++i)
        UTEST_EQUAL(TEXT("Write/Read Node Component"), componentDataA[i].Value, kTestWrintingValue);

    delete chunk;
	return fix.Finalize(*this);
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Chunk_New_ChunkComponentPod, "Pnc.1Chunk.0New.ChunkComponentPod", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Chunk_New_ChunkComponentPod::RunTest(const FString& Parameters)
{
    Fix fix;
    auto* chunk = new PNC::Chunk(&fix.Data->StructureV, kTestNodeCapacity, kTestNodeCount);
    UTEST_TRUE(TEXT("Has Chunk"), !!chunk);
    auto& internalChunk = PNC::Chunk::GetInternalChunk(*chunk);
    UTEST_EQUAL(TEXT("Node Capacity"), chunk->GetNodeCapacity(), kTestNodeCapacity);
    UTEST_EQUAL(TEXT("Node Count"), chunk->GetNodeCount(), kTestNodeCount);

    auto* componentDataV = chunk->GetComponentData<Fix::V>();
    UTEST_TRUE(TEXT("Has Chunk Component V"), !!componentDataV);

    componentDataV[0].Value = kTestWrintingValue;
    UTEST_EQUAL(TEXT("Write/Read Chunk Component"), componentDataV[0].Value, kTestWrintingValue);

    delete chunk;
    return fix.Finalize(*this);
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Chunk_New_NodeComponentCtorDtor, "Pnc.1Chunk.0New.NodeComponentCtorDtor", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Chunk_New_NodeComponentCtorDtor::RunTest(const FString& Parameters)
{
    Fix fix;
    auto* chunk = new PNC::Chunk(&fix.Data->StructureB, kTestNodeCapacity, kTestNodeCount);
    UTEST_TRUE(TEXT("Has Chunk"), !!chunk);
    UTEST_EQUAL(TEXT("Must call Component B constructor"), CallCounter::Instance.B.Ctor, kTestNodeCount);
    UTEST_EQUAL(TEXT("Must not call Component B destructor"), CallCounter::Instance.B.Dtor, kTest0);
    UTEST_EQUAL(TEXT("Must not call Component B copy constructor"), CallCounter::Instance.B.CopyCtor, kTest0);
    UTEST_EQUAL(TEXT("Must not call Component B move constructor"), CallCounter::Instance.B.MoveCtor, kTest0);
    UTEST_EQUAL(TEXT("Must not call Component B copy assignment"), CallCounter::Instance.B.CopyAssign, kTest0);
    UTEST_EQUAL(TEXT("Must not call Component B move assignment"), CallCounter::Instance.B.MoveAssign, kTest0);
    ResetCallCounter();

    auto* componentDataB = chunk->GetComponentData<Fix::B>();
    UTEST_TRUE(TEXT("Has NodeComponent B"), !!componentDataB);
    for (PNC::Size_t i = 0; i < kTestNodeCount; ++i)
        UTEST_EQUAL(TEXT("Read Contructed Node Component Value"), componentDataB[i].Value, kTestConstructingValue);

    delete chunk;
    UTEST_EQUAL(TEXT("Must not call Component B constructor"), CallCounter::Instance.B.Ctor, kTest0);
    UTEST_EQUAL(TEXT("Must call Component B destructor"), CallCounter::Instance.B.Dtor, kTestNodeCount);
    UTEST_EQUAL(TEXT("Must not call Component B copy constructor"), CallCounter::Instance.B.CopyCtor, kTest0);
    UTEST_EQUAL(TEXT("Must not call Component B move constructor"), CallCounter::Instance.B.MoveCtor, kTest0);
    UTEST_EQUAL(TEXT("Must not call Component B copy assignment"), CallCounter::Instance.B.CopyAssign, kTest0);
    UTEST_EQUAL(TEXT("Must not call Component B move assignment"), CallCounter::Instance.B.MoveAssign, kTest0);
    return fix.Finalize(*this);
}
IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Chunk_New_ChunkComponentCtorDtor, "Pnc.1Chunk.0New.ChunkComponentCtorDtor", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Chunk_New_ChunkComponentCtorDtor::RunTest(const FString& Parameters)
{
    Fix fix;
    auto* chunk = new PNC::Chunk(&fix.Data->StructureW, kTestNodeCapacity, kTestNodeCount);
    UTEST_TRUE(TEXT("Has Chunk"), !!chunk);
    UTEST_EQUAL(TEXT("Must call Component W constructor"), CallCounter::Instance.W.Ctor, kTest1);
    UTEST_EQUAL(TEXT("Must not call Component W destructor"), CallCounter::Instance.W.Dtor, kTest0);
    UTEST_EQUAL(TEXT("Must not call Component W copy constructor"), CallCounter::Instance.W.CopyCtor, kTest0);
    UTEST_EQUAL(TEXT("Must not call Component W move constructor"), CallCounter::Instance.W.MoveCtor, kTest0);
    UTEST_EQUAL(TEXT("Must not call Component W copy assignment"), CallCounter::Instance.W.CopyAssign, kTest0);
    UTEST_EQUAL(TEXT("Must not call Component W move assignment"), CallCounter::Instance.W.MoveAssign, kTest0);
    ResetCallCounter();

    auto* componentDataW = chunk->GetComponentData<Fix::W>();
    UTEST_TRUE(TEXT("Has ChunkComponent W"), !!componentDataW);
    for (PNC::Size_t i = 0; i < kTest1; ++i)
        UTEST_EQUAL(TEXT("Read Contructed Chunk Component Value"), componentDataW[i].Value, kTestConstructingValue);

    delete chunk;
    UTEST_EQUAL(TEXT("Must not call Component W constructor"), CallCounter::Instance.W.Ctor, kTest0);
    UTEST_EQUAL(TEXT("Must call Component W destructor"), CallCounter::Instance.W.Dtor, kTest1);
    UTEST_EQUAL(TEXT("Must not call Component W copy constructor"), CallCounter::Instance.W.CopyCtor, kTest0);
    UTEST_EQUAL(TEXT("Must not call Component W move constructor"), CallCounter::Instance.W.MoveCtor, kTest0);
    UTEST_EQUAL(TEXT("Must not call Component W copy assignment"), CallCounter::Instance.W.CopyAssign, kTest0);
    UTEST_EQUAL(TEXT("Must not call Component W move assignment"), CallCounter::Instance.W.MoveAssign, kTest0);
    return fix.Finalize(*this);
}

#pragma endregion



#pragma region CopyConstructor
// TODO CopyConstruct from NullChunk
// TODO CopyConstruct To NullChunk
IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Chunk_CopyConstruction_NodeComponentPod, "Pnc.1Chunk.1CopyConstruction.NodeComponentPod", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Chunk_CopyConstruction_NodeComponentPod::RunTest(const FString& Parameters)
{
    Fix fix;
    auto* chunkFrom = new PNC::Chunk(&fix.Data->StructureA, kTestNodeCapacity, kTestNodeCount);
    UTEST_TRUE(TEXT("Has Chunk from"), !!chunkFrom);

    auto* componentDataAFrom = chunkFrom->GetComponentData<Fix::A>();
    UTEST_TRUE(TEXT("ChunkFrom Has Node Component A"), !!componentDataAFrom);

    // Set data to copy from with a known value to test the copy.
    for (PNC::Size_t i = 0; i < kTestNodeCount; ++i)
        componentDataAFrom[i].Value = kTestWrintingValue;

    auto* chunkTo = new PNC::Chunk(*chunkFrom);
    UTEST_TRUE(TEXT("Has Chunk To"), !!chunkTo);

    auto* componentDataATo = chunkTo->GetComponentData<Fix::A>();
    UTEST_TRUE(TEXT("ChunkTo Has Node Component A"), !!componentDataATo);

    for (PNC::Size_t i = 0; i < kTestNodeCount; ++i)
        UTEST_EQUAL(TEXT("Copied Data of Node Component A"), componentDataATo[i].Value, kTestWrintingValue);

    delete chunkTo;
    delete chunkFrom;
    return fix.Finalize(*this);
}
IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Chunk_CopyConstruction_ChunkComponentPod, "Pnc.1Chunk.1CopyConstruction.ChunkComponentPod", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Chunk_CopyConstruction_ChunkComponentPod::RunTest(const FString& Parameters)
{
    Fix fix;
    auto* chunkFrom = new PNC::Chunk(&fix.Data->StructureV, kTestNodeCapacity, kTestNodeCount);
    UTEST_TRUE(TEXT("Has Chunk from"), !!chunkFrom);

    auto* componentDataVFrom = chunkFrom->GetComponentData<Fix::V>();
    UTEST_TRUE(TEXT("ChunkFrom Has Chunk Component V"), !!componentDataVFrom);

    // Set data to copy from with a known value to test the copy.
    componentDataVFrom[0].Value = kTestWrintingValue;

    auto* chunkTo = new PNC::Chunk(*chunkFrom);
    UTEST_TRUE(TEXT("Has Chunk To"), !!chunkTo);

    auto* componentDataVTo = chunkTo->GetComponentData<Fix::V>();
    UTEST_TRUE(TEXT("ChunkTo Has Chunk Component V"), !!componentDataVTo);

    UTEST_EQUAL(TEXT("Copied Data of Chunk Component V"), componentDataVTo[0].Value, kTestWrintingValue);

    delete chunkTo;
    delete chunkFrom;
    return fix.Finalize(*this);
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Chunk_CopyConstruction_NodeComponentCopyConstructor, "Pnc.1Chunk.1CopyConstruction.NodeComponentCopyConstructor", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Chunk_CopyConstruction_NodeComponentCopyConstructor::RunTest(const FString& Parameters)
{
    Fix fix;
    auto* chunkFrom = new PNC::Chunk(&fix.Data->StructureB, kTestNodeCapacity, kTestNodeCount);
    UTEST_TRUE(TEXT("Has Chunk from"), !!chunkFrom);

    auto* componentDataBFrom = chunkFrom->GetComponentData<Fix::B>();
    UTEST_TRUE(TEXT("ChunkFrom Has Node Component B"), !!componentDataBFrom);

    // Overwrite data to copy from with different value so it copies over the kTestConstructingValue set by the default constructor.
    for (PNC::Size_t i = 0; i < kTestNodeCount; ++i)
        componentDataBFrom[i].Value = kTestWrintingValue;

    ResetCallCounter();
    auto* chunkTo = new PNC::Chunk(*chunkFrom);
    UTEST_TRUE(TEXT("Has Chunk To"), !!chunkTo);
    auto* componentDataBTo = chunkTo->GetComponentData<Fix::B>();
    UTEST_TRUE(TEXT("ChunkTo Has Node Component B"), !!componentDataBTo);
    UTEST_EQUAL(TEXT("Must not call Component B constructor"), CallCounter::Instance.B.Ctor, kTest0);
    UTEST_EQUAL(TEXT("Must not call Component B destructor"), CallCounter::Instance.B.Dtor, kTest0);
    UTEST_EQUAL(TEXT("Must call Component B copy constructor"), CallCounter::Instance.B.CopyCtor, kTestNodeCount);
    UTEST_EQUAL(TEXT("Must not call Component B move constructor"), CallCounter::Instance.B.MoveCtor, kTest0);
    UTEST_EQUAL(TEXT("Must not call Component B copy assignment"), CallCounter::Instance.B.CopyAssign, kTest0);
    UTEST_EQUAL(TEXT("Must not call Component B move assignment"), CallCounter::Instance.B.MoveAssign, kTest0);

    for (PNC::Size_t i = 0; i < kTestNodeCount; ++i)
        UTEST_EQUAL(TEXT("Copied Data of Node Component B"), componentDataBTo[i].Value, kTestWrintingValue);

    delete chunkTo;
    delete chunkFrom;
    return fix.Finalize(*this);
}
IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Chunk_CopyConstruction_ChunkComponentCopyConstructor, "Pnc.1Chunk.1CopyConstruction.ChunkComponentCopyConstructor", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Chunk_CopyConstruction_ChunkComponentCopyConstructor::RunTest(const FString& Parameters)
{
    Fix fix;
    auto* chunkFrom = new PNC::Chunk(&fix.Data->StructureW, kTestNodeCapacity, kTestNodeCount);
    UTEST_TRUE(TEXT("Has Chunk from"), !!chunkFrom);

    auto* componentDataWFrom = chunkFrom->GetComponentData<Fix::W>();
    UTEST_TRUE(TEXT("ChunkFrom Has Node Component W"), !!componentDataWFrom);

    // Overwrite data to copy from with different value so it copies over the kTestConstructingValue set by the default constructor.
    componentDataWFrom[0].Value = kTestWrintingValue;

    ResetCallCounter();
    auto* chunkTo = new PNC::Chunk(*chunkFrom);
    UTEST_TRUE(TEXT("Has Chunk To"), !!chunkTo);
    auto* componentDataWTo = chunkTo->GetComponentData<Fix::W>();
    UTEST_TRUE(TEXT("ChunkTo Has Node Component W"), !!componentDataWTo);
    UTEST_EQUAL(TEXT("Must not call Component W constructor"), CallCounter::Instance.W.Ctor, kTest0);
    UTEST_EQUAL(TEXT("Must not call Component W destructor"), CallCounter::Instance.W.Dtor, kTest0);
    UTEST_EQUAL(TEXT("Must call Component W copy constructor"), CallCounter::Instance.W.CopyCtor, kTest1);
    UTEST_EQUAL(TEXT("Must not call Component W move constructor"), CallCounter::Instance.W.MoveCtor, kTest0);
    UTEST_EQUAL(TEXT("Must not call Component W copy assignment"), CallCounter::Instance.W.CopyAssign, kTest0);
    UTEST_EQUAL(TEXT("Must not call Component W move assignment"), CallCounter::Instance.W.MoveAssign, kTest0);

    UTEST_EQUAL(TEXT("Copied Data of Node Component W"), componentDataWTo[0].Value, kTestWrintingValue);

    delete chunkTo;
    delete chunkFrom;
    return fix.Finalize(*this);
}

#pragma endregion


#pragma region CopyAssignment
// Copy to self
// Copy to chunk with enough space
// Copy to chunk with not enough space
// Copy from NullChunk
// Copy to NullChunk

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Chunk_CopyAssignment_NodeComponentPod, "Pnc.1Chunk.2CopyAssignment.NodeComponentPod", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Chunk_CopyAssignment_NodeComponentPod::RunTest(const FString& Parameters)
{
    Fix fix;
    auto* chunkFrom = new PNC::Chunk(&fix.Data->StructureA, kTestNodeCapacity, kTestNodeCount);
    UTEST_TRUE(TEXT("Valid Chunk from"), !!chunkFrom);

    auto* componentDataAFrom = chunkFrom->GetComponentData<Fix::A>();
    UTEST_TRUE(TEXT("ChunkFrom has NodeComponent A"), !!componentDataAFrom);

    // Set data to copy from with a known value to test the copy.
    for (PNC::Size_t i = 0; i < kTestNodeCount; ++i)
        componentDataAFrom[i].Value = kTestWrintingValue;

    auto* chunkTo = new PNC::Chunk(&fix.Data->StructureA, kTestNodeCapacity, kTestNodeCount);
    UTEST_TRUE(TEXT("Valid Chunk To"), !!chunkTo);

    // Copy assign
    *chunkTo = *chunkFrom;

    auto* componentDataATo = chunkTo->GetComponentData<Fix::A>();
    UTEST_TRUE(TEXT("ChunkTo has NodeComponent A"), !!componentDataATo);

    for (PNC::Size_t i = 0; i < kTestNodeCount; ++i)
        UTEST_EQUAL(TEXT("Data for NodeComponent A must be copied"), componentDataATo[i].Value, kTestWrintingValue);

    delete chunkTo;
    delete chunkFrom;
    return fix.Finalize(*this);
}
IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Chunk_CopyAssignment_ChunkComponentPod, "Pnc.1Chunk.2CopyAssignment.ChunkComponentPod", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Chunk_CopyAssignment_ChunkComponentPod::RunTest(const FString& Parameters)
{
    Fix fix;
    auto* chunkFrom = new PNC::Chunk(&fix.Data->StructureV, kTestNodeCapacity, kTestNodeCount);
    UTEST_TRUE(TEXT("Valid Chunk from"), !!chunkFrom);

    auto* componentDataVFrom = chunkFrom->GetComponentData<Fix::V>();
    UTEST_TRUE(TEXT("ChunkFrom has ChunkComponent V"), !!componentDataVFrom);

    // Set data to copy from with a known value to test the copy.
    componentDataVFrom[0].Value = kTestWrintingValue;

    auto* chunkTo = new PNC::Chunk(&fix.Data->StructureA, kTestNodeCapacity, kTestNodeCount);
    UTEST_TRUE(TEXT("Valid Chunk To"), !!chunkTo);

    // Copy assign
    *chunkTo = *chunkFrom;

    auto* componentDataVTo = chunkTo->GetComponentData<Fix::V>();
    UTEST_TRUE(TEXT("ChunkTo has Chunk Component V"), !!componentDataVTo);

    UTEST_EQUAL(TEXT("Data for ChunkComponent V must be copied"), componentDataVTo[0].Value, kTestWrintingValue);

    delete chunkTo;
    delete chunkFrom;
    return fix.Finalize(*this);
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Chunk_CopyAssignment_NodeComponentCopyConstructor, "Pnc.1Chunk.2CopyAssignment.NodeComponentCopyConstructor", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Chunk_CopyAssignment_NodeComponentCopyConstructor::RunTest(const FString& Parameters)
{
    Fix fix;
    auto* chunkFrom = new PNC::Chunk(&fix.Data->StructureB, kTestNodeCapacity, kTestNodeCount);
    UTEST_TRUE(TEXT("Valid Chunk from"), !!chunkFrom);

    auto* componentDataBFrom = chunkFrom->GetComponentData<Fix::B>();
    UTEST_TRUE(TEXT("ChunkFrom has NodeComponent B"), !!componentDataBFrom);

    // Overwrite data to copy from with different value so it copies over the kTestConstructingValue set by the default constructor.
    for (PNC::Size_t i = 0; i < kTestNodeCount; ++i)
        componentDataBFrom[i].Value = kTestWrintingValue;

    auto* chunkTo = new PNC::Chunk(&fix.Data->StructureA, kTestNodeCapacity, kTestNodeCount);
    UTEST_TRUE(TEXT("Valid Chunk To"), !!chunkTo);

    auto* componentDataBTo = chunkTo->GetComponentData<Fix::B>();
    UTEST_TRUE(TEXT("ChunkTo has NodeComponent B"), !!componentDataBTo);

    for (PNC::Size_t i = 0; i < kTestNodeCount; ++i)
        UTEST_EQUAL(TEXT("ChunkTo NodeComponent B must be constructed"), componentDataBTo[i].Value, kTestConstructingValue);


    ResetCallCounter();
    // Copy assign
    *chunkTo = *chunkFrom;

    UTEST_EQUAL(TEXT("Must not call Component B constructor"), CallCounter::Instance.B.Ctor, kTest0);
    UTEST_EQUAL(TEXT("Must not call Component B destructor"), CallCounter::Instance.B.Dtor, kTest0);
    UTEST_EQUAL(TEXT("Must not call Component B copy constructor"), CallCounter::Instance.B.CopyCtor, kTest0);
    UTEST_EQUAL(TEXT("Must not call Component B move constructor"), CallCounter::Instance.B.MoveCtor, kTest0);
    UTEST_EQUAL(TEXT("Must call Component B copy assignment"), CallCounter::Instance.B.CopyAssign, kTestNodeCount);
    UTEST_EQUAL(TEXT("Must not call Component B move assignment"), CallCounter::Instance.B.MoveAssign, kTest0);

    componentDataBTo = chunkTo->GetComponentData<Fix::B>();
    UTEST_TRUE(TEXT("ChunkTo has NodeComponent B"), !!componentDataBTo);

    for (PNC::Size_t i = 0; i < kTestNodeCount; ++i)
        UTEST_EQUAL(TEXT("Data for NodeComponent B must be copied"), componentDataBTo[i].Value, kTestWrintingValue);

    delete chunkTo;
    delete chunkFrom;
    return fix.Finalize(*this);
}
IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Chunk_CopyAssignment_ChunkComponentCopyConstructor, "Pnc.1Chunk.2CopyAssignment.ChunkComponentCopyConstructor", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Chunk_CopyAssignment_ChunkComponentCopyConstructor::RunTest(const FString& Parameters)
{
    Fix fix;
    auto* chunkFrom = new PNC::Chunk(&fix.Data->StructureW, kTestNodeCapacity, kTestNodeCount);
    UTEST_TRUE(TEXT("Valid Chunk from"), !!chunkFrom);

    auto* componentDataWFrom = chunkFrom->GetComponentData<Fix::W>();
    UTEST_TRUE(TEXT("ChunkFrom has ChunkComponent W"), !!componentDataWFrom);

    // Overwrite data to copy from with different value so it copies over the kTestConstructingValue set by the default constructor.
    componentDataWFrom[0].Value = kTestWrintingValue;

    auto* chunkTo = new PNC::Chunk(&fix.Data->StructureA, kTestNodeCapacity, kTestNodeCount);
    UTEST_TRUE(TEXT("Valid Chunk To"), !!chunkTo);

    ResetCallCounter();
    // Copy assign
    *chunkTo = *chunkFrom;

    UTEST_EQUAL(TEXT("Must not call Component W constructor"), CallCounter::Instance.W.Ctor, kTest0);
    UTEST_EQUAL(TEXT("Must not call Component W destructor"), CallCounter::Instance.W.Dtor, kTest0);
    UTEST_EQUAL(TEXT("Must not call Component W copy constructor"), CallCounter::Instance.W.CopyCtor, kTest0);
    UTEST_EQUAL(TEXT("Must not call Component W move constructor"), CallCounter::Instance.W.MoveCtor, kTest0);
    UTEST_EQUAL(TEXT("Must call Component W copy assignment"), CallCounter::Instance.W.CopyAssign, kTest1);
    UTEST_EQUAL(TEXT("Must not call Component W move assignment"), CallCounter::Instance.W.MoveAssign, kTest0);

    auto* componentDataWTo = chunkTo->GetComponentData<Fix::W>();
    UTEST_TRUE(TEXT("ChunkTo has ChunkComponent W"), !!componentDataWTo);
    UTEST_EQUAL(TEXT("Data for ChunkComponent W must be copied"), componentDataWTo[0].Value, kTestWrintingValue);

    delete chunkTo;
    delete chunkFrom;
    return fix.Finalize(*this);
}

#pragma endregion

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPncChunkArrayNew, "Pnc.2ChunkArray.0NewA", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPncChunkArrayNew::RunTest(const FString& Parameters)
{
    Fix fix;
    delete new PNC::ChunkArray(&fix.Data->StructureA, kTestNodeCapacity, kTestChunkCapacity, kTestChunkCount0, kTestNodeCount0);
    return fix.Finalize(*this);
}


//
//
//IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPncChunkAddNode, "Pnc.1Chunk.1AddNode", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
//bool TestPncChunkAddNode::RunTest(const FString& Parameters)
//{
//    FixChunk fix;
//    auto nodeIndex = fix.Chunk->AddNode();
//    
//    return fix.Finalize(*this);
//}
//
//
//IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPncChunkCopy, "Pnc.1Chunk.Copy", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
//bool TestPncChunkCopy::RunTest(const FString& Parameters)
//{
//    FixChunk fix;
//    auto* chunkCopy = new PNC::Chunk(*fix.Chunk);
//    return fix.Finalize(*this);
//}



//
//struct PncTestFixtureRegistry
//{
//public:
//
//    using A = TestNodeComponentA;
//    using B = TestNodeComponentB;
//    using V = TestChunkComponentV;
//    using W = TestChunkComponentW;
//public:
//    bool Failed;
//    PNC::PncRegistry* PncRegistry;
//
//    const PNC::ChunkStructure* StructureA;
//    const PNC::ChunkStructure* StructureB;
//    const PNC::ChunkStructure* StructureAB;
//    const PNC::ChunkStructure* StructureV;
//    const PNC::ChunkStructure* StructureVW;
//    const PNC::ChunkStructure* StructureAV;
//    const PNC::ChunkStructure* StructureBV;
//    const PNC::ChunkStructure* StructureABV;
//    const PNC::ChunkStructure* StructureAVW;
//    const PNC::ChunkStructure* StructureBVW;
//    const PNC::ChunkStructure* StructureABVW;
//
//    PncTestFixtureRegistry()
//        : Failed(false)
//    {
//        PncRegistry = new PNC::PncRegistry();
//        InitializeChunkStructures();
//    }
//    PncTestFixtureRegistry(const PncTestFixtureRegistry& o) = delete;
//    PncTestFixtureRegistry& operator=(const PncTestFixtureRegistry& o) = delete;
//    PncTestFixtureRegistry(PncTestFixtureRegistry&& o) = delete;
//    PncTestFixtureRegistry& operator=(PncTestFixtureRegistry&& o) = delete;
//    ~PncTestFixtureRegistry()
//    {
//        bool success = Finalize();
//        ensure(success);
//    }
//
//    void InitializeChunkStructures()
//    {
//        StructureA = PncRegistry->GetOrAddChunkStructure<A>();
//        StructureB = PncRegistry->GetOrAddChunkStructure<B>();
//        StructureAB = PncRegistry->GetOrAddChunkStructure<A, B>();
//        StructureV = PncRegistry->GetOrAddChunkStructure<V>();
//        StructureVW = PncRegistry->GetOrAddChunkStructure<V, W>();
//        StructureAV = PncRegistry->GetOrAddChunkStructure<A, V>();
//        StructureBV = PncRegistry->GetOrAddChunkStructure<B, V>();
//        StructureABV = PncRegistry->GetOrAddChunkStructure<A, B, V>();
//        StructureAVW = PncRegistry->GetOrAddChunkStructure<A, V, W>();
//        StructureBVW = PncRegistry->GetOrAddChunkStructure<B, V, W>();
//        StructureABVW = PncRegistry->GetOrAddChunkStructure<A, B, V, W>();
//
//        Failed |= !StructureA
//            || !StructureB
//            || !StructureAB
//            || !StructureV
//            || !StructureVW
//            || !StructureAV
//            || !StructureBV
//            || !StructureABV
//            || !StructureAVW
//            || !StructureBVW
//            || !StructureABVW;
//    }
//    bool Finalize()
//    {
//        if (PncRegistry == nullptr)
//            return true;
//
//        delete PncRegistry;
//        PncRegistry = nullptr;
//        return PNC::MemoryTracker<>::AllocationCount == 0;
//    }
//};

//
//
//IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPncRegistryChunkNew, "Pnc.Registry.Chunk.0New", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
//bool TestPncRegistryChunkNew::RunTest(const FString& Parameters)
//{
//    Fix fix;
//
//    new PNC::Chunk(fix.Data->StructureA, 16, 4);
//    auto* chunk = fix.PncRegistry->NewChunk(fix.StructureA, 4, 0);
//    fix.Failed |= !chunk;
//
//    return fix.Finalize();
//}
//
//IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPncRegistryChunkDelete, "Pnc.Registry.Chunk.1Delete", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
//bool TestPncRegistryChunkDelete::RunTest(const FString& Parameters)
//{
//    Fix fix;
//
//    auto* chunk = fix.PncRegistry->NewChunk(fix.StructureA, 4, 0);
//    fix.PncRegistry->DeleteChunk(chunk);
//    fix.Failed |= !chunk;
//
//    return fix.Finalize();
//}
//
//
//IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPncRegistryChunkArrayNew, "Pnc.Registry.ChunkArray.0New", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
//bool TestPncRegistryChunkArrayNew::RunTest(const FString& Parameters)
//{
//    Fix fix;
//
//    auto* chunk = fix.PncRegistry->NewChunkArray(fix.StructureA, 4, 0, 0, 0);
//    fix.Failed |= !chunk;
//
//    return fix.Finalize();
//}
//
//IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPncRegistryChunkArrayDelete, "Pnc.Registry.ChunkArray.1Delete", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
//bool TestPncRegistryChunkArrayDelete::RunTest(const FString& Parameters)
//{
//    Fix fix;
//
//    auto* chunk = fix.PncRegistry->NewChunkArray(fix.StructureA, 4, 0, 0, 0);
//    fix.PncRegistry->DeleteChunk(chunk);
//    fix.Failed |= !chunk;
//
//    return fix.Finalize();
//}