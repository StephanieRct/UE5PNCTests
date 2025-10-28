// Fill out your copyright notice in the Description page of Project Settings.


#include "ChunkPointerComponentTest.h"
#include "UE5PNC/public/PncDefault.h"

#define FIXSTART(FixtureType) FixtureType fix; try { do{}while(0)

#define FIXEND }\
    catch (const FString& msg)\
    {\
        UTEST_TRUE(FString::Printf(TEXT("Unexpected FString exception: %s"), *msg), false);\
    }\
    catch (...)\
    {\
        UTEST_TRUE(TEXT("Unexpected unknown exception"), false);\
    } return fix.Finalize(*this)


constexpr int kTestConstructingValue = 99;
constexpr int kTestWrintingValue = 50;
constexpr PNC::Size_t kSize_NodeCapacity = 16;
constexpr PNC::Size_t kSize_NodeCapacityMidStart = 5;
constexpr PNC::Size_t kSize_NodeCapacityMidCount = 5;
constexpr PNC::Size_t kSize_NodeCount0 = 0;
constexpr PNC::Size_t kSize_NodeCount = 8;
constexpr PNC::Size_t kSize_ChunkCapacity = 12;
constexpr PNC::Size_t kSize_ChunkCount0 = 0;
constexpr PNC::Size_t kSize_ChunkCount = 6;
constexpr PNC::Size_t kSize_1 = 1;
constexpr PNC::Size_t kSize_0 = 0;

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

    int AllocationCountBefore;
    PncTestData* Data;
    bool Failed;

    PncTestFixture()
        : AllocationCountBefore(pnc_allocation_count)
        , Data(new PncTestData())
        , Failed(false)
    {
        ResetCallCounter();
    }
    PncTestFixture(const PncTestFixture& o) = delete;
    PncTestFixture& operator=(const PncTestFixture& o) = delete;
    PncTestFixture(PncTestFixture&& o) = delete;
    PncTestFixture& operator=(PncTestFixture&& o) = delete;
    //~PncTestFixture()
    //{
    //    ensureMsgf(Data == nullptr, TEXT("PncTestFixture::Finalize must be called before detroying the fixture."));
    //}

    bool Finalize(FAutomationTestBase& test)
    {
        delete Data;
        Data = nullptr;
        if (!test.TestEqual(TEXT("Remaining allocations count"), pnc_allocation_count, AllocationCountBefore))
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
        : Chunk(new PNC::Chunk(&Data->StructureA, kSize_NodeCapacity, kSize_NodeCount0))
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

void TestAssert()
{
    pnc_assert(false == true);
}
void TestAssertf(int a)
{
    pnc_assertf(false == true, TEXT("This is my assertf with argument of value '%d'"), a);
}
void TestAssertNoEntry()
{
    pnc_assert_no_entry_return();
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Fixture_Exceptions, "Pnc.0Fixture.Exceptions", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Fixture_Exceptions::RunTest(const FString& Parameters)
{
    try
    {
        TestAssert();
        UTEST_TRUE(TEXT("pnc_assert must throw an execption"), false);
    }
    catch (const FString& msg)
    {
        UE_LOG(LogTemp, Log, TEXT("Catch execption '%s'"), *msg);
    }
    catch(...)
    {
        UTEST_TRUE(TEXT("pnc_assert throws unknown execption, should be a FString"), false);
    }

    try
    {
        TestAssertf(5);
        UTEST_TRUE(TEXT("pnc_assertf must throw an execption"), false);
    }
    catch (const FString& msg)
    {
        UE_LOG(LogTemp, Log, TEXT("Catch execption '%s'"), *msg);
    }
    catch (...)
    {
        UTEST_TRUE(TEXT("pnc_assertf throws unknown execption, should be a FString"), false);
    }

    try
    {
        TestAssertNoEntry();
        UTEST_TRUE(TEXT("pnc_assert_no_entry_return must throw an execption"), false);
    }
    catch (const FString& msg)
    {
        UE_LOG(LogTemp, Log, TEXT("Catch execption '%s'"), *msg);
    }
    catch (...)
    {
        UTEST_TRUE(TEXT("pnc_assert_no_entry_return throws unknown execption, should be a FString"), false);
    }

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Fixture_Data, "Pnc.0Fixture.Data", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Fixture_Data::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);
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
    
    FIXEND;
}

template<typename TChunk>
bool ChunkIsValidStructData(FAutomationTestBase& test, TChunk* const  chunk, const PNC::Size_t nodeCount, const PNC::Size_t nodeCapacity)
{
    if (!test.TestTrue(TEXT("Chunk is allocated"), !!chunk))
        return false;

    if (!test.TestTrue(TEXT("Chunk is StructData"), chunk->IsStructData()))
        return false;

    if (!test.TestEqual(TEXT("Chunk's Node Count"), chunk->GetNodeCount(), nodeCount))
        return false;

    if (!test.TestEqual(TEXT("Chunk's Node Capacity"), chunk->GetNodeCapacity(), nodeCapacity))
        return false;

    auto& internalChunk = PNC::ChunkPointer::GetInternalChunk(*chunk);
    auto componentTypeCount = internalChunk.Structure->GetComponentCount();

    if (!test.TestTrue(TEXT("Chunk has valid ComponentDataArray Memory"), pnc_owns(internalChunk.ComponentData, componentTypeCount)))
        return false;
    for (PNC::Size_t i = 0; i < componentTypeCount; ++i)
    {
        const auto* componentType = internalChunk.Structure->Components[i];
        uint8* begin = (uint8*) internalChunk.ComponentData[i];
        PNC::Size_t size = 0;

        switch (componentType->GetOwner())
        {
            case PNC::ComponentOwner_Node:
                size = internalChunk.NodeCount * componentType->GetSize();
                break;
            case PNC::ComponentOwner_Chunk:
                size = componentType->GetSize();
                break;
            default:
                pnc_assert_no_entry_return(false);
        }

        if (!test.TestTrue(TEXT("Chunk has valid ComponentData Memory"), pnc_owns(begin, size)))
            return false;
    }
}

#define TEST_VALID_CHUNK_VOIDNULL(chunk) \
    UTEST_TRUE(TEXT(#chunk " is VoidNull"), chunk->IsVoidNull());\
    UTEST_EQUAL(TEXT("VoidNull Chunk '" #chunk "' NodeCount"), chunk->GetNodeCount(), kSize_0)

#define TEST_VALID_CHUNK_STRUCTDATA(chunk, nodeCount, nodeCapacity)\
    {\
        UTEST_TRUE(TEXT("Chunk is allocated"), !!chunk);\
        UTEST_TRUE(TEXT("Chunk is StructData"), chunk->IsStructData());\
        UTEST_EQUAL(TEXT("Chunk's Node Count"), chunk->GetNodeCount(), nodeCount);\
        UTEST_EQUAL(TEXT("Chunk's Node Capacity"), chunk->GetNodeCapacity(), nodeCapacity);\
        \
        auto& internalChunk = PNC::ChunkPointer::GetInternalChunk(*chunk);\
        auto componentTypeCount = internalChunk.Structure->GetComponentCount();\
        \
        UTEST_TRUE(TEXT("Chunk has valid ComponentDataArray Memory"), pnc_owns(internalChunk.ComponentData, componentTypeCount));\
        \
        for (PNC::Size_t i = 0; i < componentTypeCount; ++i)\
        {\
            const auto* componentType = internalChunk.Structure->Components[i];\
            uint8* begin = (uint8*)internalChunk.ComponentData[i];\
            PNC::Size_t size = 0;\
            \
            switch (componentType->GetOwner())\
            {\
            case PNC::ComponentOwner_Node:\
                size = internalChunk.NodeCount * componentType->GetSize();\
                break;\
            case PNC::ComponentOwner_Chunk:\
                size = componentType->GetSize();\
                break;\
            default:\
                pnc_assert_no_entry_return(false);\
            }\
            \
            UTEST_TRUE(TEXT("Chunk has valid ComponentData Memory"), pnc_owns(begin, size));\
        }\
    }do{}while(0)

#define WRITE_COMPONENT(chunk, ComponentType, count, value)\
    {\
        auto* componentData = chunk->GetComponentData<ComponentType>();\
        UTEST_TRUE(TEXT(#chunk " Has Component " #ComponentType), !!componentData);\
        for (PNC::Size_t i = 0; i < count; ++i)\
            componentData[i].Value = value;\
    }do{}while(0)

#define TEST_COMPONENT_VALUE(afterWhat, chunk, ComponentType, count, value)\
    {\
        auto* componentData = chunk->GetComponentData<ComponentType>();\
        UTEST_TRUE(TEXT(#chunk " Has Component " #ComponentType), !!componentData);\
        for (PNC::Size_t i = 0; i < count; ++i)\
            UTEST_EQUAL(TEXT("Value after " afterWhat), componentData[i].Value, value);\
    }do{}while(0)


// TODO ChunkPointer.Construct VoidData

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_ChunkPointer_Construct_VoidNull, "Pnc.1-ChunkPointer.0-Construct-VoidNull", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_ChunkPointer_Construct_VoidNull::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);
    auto* chunk = new PNC::ChunkPointer();
    UTEST_TRUE (TEXT("Chunk is Void"),       chunk->IsVoid());
    UTEST_TRUE (TEXT("Chunk is Null"),       chunk->IsNull());
    UTEST_FALSE(TEXT("Chunk is Struct"),     chunk->IsStruct());
    UTEST_FALSE(TEXT("Chunk is Data"),       chunk->IsData());
    UTEST_TRUE (TEXT("Chunk is VoidNull"),   chunk->IsVoidNull());
    UTEST_FALSE(TEXT("Chunk is VoidData"),   chunk->IsVoidData());
    UTEST_FALSE(TEXT("Chunk is StructNull"), chunk->IsStructNull());
    UTEST_FALSE(TEXT("Chunk is StructData"), chunk->IsStructData());
    delete chunk;
    FIXEND;
}
IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_ChunkPointer_Construct_StructNull, "Pnc.1-ChunkPointer.0-Construct-StructNull", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_ChunkPointer_Construct_StructNull::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);
    auto* chunk = new PNC::ChunkPointer(&fix.Data->StructureABVW);
    UTEST_FALSE(TEXT("Chunk is Void"),       chunk->IsVoid());
    UTEST_TRUE (TEXT("Chunk is Null"),       chunk->IsNull());
    UTEST_TRUE (TEXT("Chunk is Struct"),     chunk->IsStruct());
    UTEST_FALSE(TEXT("Chunk is Data"),       chunk->IsData());
    UTEST_FALSE(TEXT("Chunk is VoidNull"),   chunk->IsVoidNull());
    UTEST_FALSE(TEXT("Chunk is VoidData"),   chunk->IsVoidData());
    UTEST_TRUE (TEXT("Chunk is StructNull"), chunk->IsStructNull());
    UTEST_FALSE(TEXT("Chunk is StructData"), chunk->IsStructData());
    delete chunk;
    FIXEND;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Chunk_Construct_StructData, "Pnc.2-Chunk.0-Construct-StructData", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Chunk_Construct_StructData::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);
    ResetCallCounter();
    auto* chunk = new PNC::Chunk(&fix.Data->StructureABVW, kSize_NodeCapacity, kSize_NodeCount);
    TEST_VALID_CHUNK_STRUCTDATA(chunk, kSize_NodeCount, kSize_NodeCapacity);
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),        CallCounter::Instance.B.Ctor,       kSize_NodeCount);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),         CallCounter::Instance.B.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),   CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),   CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),    CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),    CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),       CallCounter::Instance.W.Ctor,       kSize_1);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),        CallCounter::Instance.W.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),  CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),  CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),   CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),   CallCounter::Instance.W.MoveAssign, kSize_0);

    ResetCallCounter();
    delete chunk;
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),        CallCounter::Instance.B.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),         CallCounter::Instance.B.Dtor,       kSize_NodeCount);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),   CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),   CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),    CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),    CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),       CallCounter::Instance.W.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),        CallCounter::Instance.W.Dtor,       kSize_1);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),  CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),  CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),   CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),   CallCounter::Instance.W.MoveAssign, kSize_0);
    FIXEND;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Chunk_MoveConstruction, "Pnc.2-Chunk.1-MoveConstruction", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Chunk_MoveConstruction::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);
    auto* chunkFrom = new PNC::Chunk(&fix.Data->StructureABVW, kSize_NodeCapacity, kSize_NodeCount);
    TEST_VALID_CHUNK_STRUCTDATA(chunkFrom, kSize_NodeCount, kSize_NodeCapacity);

    // Set data to copy from with a known value to test the copy.
    WRITE_COMPONENT(chunkFrom, Fix::A, kSize_NodeCount, kTestWrintingValue);
    WRITE_COMPONENT(chunkFrom, Fix::B, kSize_NodeCount, kTestWrintingValue);
    WRITE_COMPONENT(chunkFrom, Fix::V, kSize_1,         kTestWrintingValue);
    WRITE_COMPONENT(chunkFrom, Fix::W, kSize_1,         kTestWrintingValue);
    
    ResetCallCounter();
    auto allocationCountBefore = pnc_allocation_count;
    auto* chunkTo = new PNC::Chunk(std::move(*chunkFrom));
    
    UTEST_EQUAL(TEXT("Allocation count"), pnc_allocation_count - allocationCountBefore, 0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),        CallCounter::Instance.B.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),         CallCounter::Instance.B.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),   CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),   CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),    CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),    CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),       CallCounter::Instance.W.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),        CallCounter::Instance.W.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),  CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),  CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),   CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),   CallCounter::Instance.W.MoveAssign, kSize_0);
    TEST_VALID_CHUNK_STRUCTDATA(chunkTo, kSize_NodeCount, kSize_NodeCapacity);
    TEST_VALID_CHUNK_VOIDNULL(chunkFrom);

    TEST_COMPONENT_VALUE("Move Construction TrivialNodeComponent",      chunkTo, Fix::A, kSize_NodeCount, kTestWrintingValue);
    TEST_COMPONENT_VALUE("Move Construction NonTrivialNodeComponent",   chunkTo, Fix::B, kSize_NodeCount, kTestWrintingValue);
    TEST_COMPONENT_VALUE("Move Construction TrivialChunkComponent",     chunkTo, Fix::V, kSize_1,         kTestWrintingValue);
    TEST_COMPONENT_VALUE("Move Construction NonTrivialChunkComponent",  chunkTo, Fix::W, kSize_1,         kTestWrintingValue);

    delete chunkTo;
    delete chunkFrom;

    FIXEND;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Chunk_MoveAssignment_Self, "Pnc.2-Chunk.2-MoveAssignment-Self", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Chunk_MoveAssignment_Self::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);

    auto* chunkFromAndTo = new PNC::Chunk(&fix.Data->StructureABVW, kSize_NodeCapacity, kSize_NodeCount);
    TEST_VALID_CHUNK_STRUCTDATA(chunkFromAndTo, kSize_NodeCount, kSize_NodeCapacity);

    auto allocationCountBefore = pnc_allocation_count;
    ResetCallCounter();
    *chunkFromAndTo = std::move(*chunkFromAndTo);
    UTEST_EQUAL(TEXT("Allocation count"), pnc_allocation_count - allocationCountBefore, 0);
    TEST_VALID_CHUNK_STRUCTDATA(chunkFromAndTo, kSize_NodeCount, kSize_NodeCapacity);
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),        CallCounter::Instance.B.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),         CallCounter::Instance.B.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),   CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),   CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),    CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),    CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),       CallCounter::Instance.W.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),        CallCounter::Instance.W.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),  CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),  CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),   CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),   CallCounter::Instance.W.MoveAssign, kSize_0);

    delete chunkFromAndTo;

    FIXEND;
}
IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Chunk_MoveAssignment_VoidNull_StructData, "Pnc.2-Chunk.2-MoveAssignment-VoidNull-StructData", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Chunk_MoveAssignment_VoidNull_StructData::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);
    auto* chunkFrom = new PNC::Chunk(&fix.Data->StructureABVW, kSize_NodeCapacity, kSize_NodeCount);
    TEST_VALID_CHUNK_STRUCTDATA(chunkFrom, kSize_NodeCount, kSize_NodeCapacity);

    // Set data to copy from with a known value to test the copy.
    WRITE_COMPONENT(chunkFrom, Fix::A, kSize_NodeCount, kTestWrintingValue);
    WRITE_COMPONENT(chunkFrom, Fix::B, kSize_NodeCount, kTestWrintingValue);
    WRITE_COMPONENT(chunkFrom, Fix::V, kSize_1,         kTestWrintingValue);
    WRITE_COMPONENT(chunkFrom, Fix::W, kSize_1,         kTestWrintingValue);

    auto* chunkTo = new PNC::Chunk();
    TEST_VALID_CHUNK_VOIDNULL(chunkTo);

    ResetCallCounter();
    auto allocationCountBefore = pnc_allocation_count;
    *chunkTo = std::move(*chunkFrom);
    UTEST_EQUAL(TEXT("Allocation count"), pnc_allocation_count - allocationCountBefore, 0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),        CallCounter::Instance.B.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),         CallCounter::Instance.B.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),   CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),   CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),    CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),    CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),       CallCounter::Instance.W.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),        CallCounter::Instance.W.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),  CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),  CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),   CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),   CallCounter::Instance.W.MoveAssign, kSize_0);
    TEST_VALID_CHUNK_STRUCTDATA(chunkTo, kSize_NodeCount, kSize_NodeCapacity);
    TEST_VALID_CHUNK_VOIDNULL(chunkFrom);

    TEST_COMPONENT_VALUE("Move Construction TrivialNodeComponent",      chunkTo, Fix::A, kSize_NodeCount, kTestWrintingValue);
    TEST_COMPONENT_VALUE("Move Construction NonTrivialNodeComponent",   chunkTo, Fix::B, kSize_NodeCount, kTestWrintingValue);
    TEST_COMPONENT_VALUE("Move Construction TrivialChunkComponent",     chunkTo, Fix::V, kSize_1,         kTestWrintingValue);
    TEST_COMPONENT_VALUE("Move Construction NonTrivialChunkComponent",  chunkTo, Fix::W, kSize_1,         kTestWrintingValue);

    delete chunkTo;
    delete chunkFrom;

    FIXEND;
}
IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Chunk_MoveAssignment_StructData_VoidNull, "Pnc.2-Chunk.2-MoveAssignment-StructData-VoidNull", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Chunk_MoveAssignment_StructData_VoidNull::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);

    auto* chunkFrom = new PNC::Chunk();
    TEST_VALID_CHUNK_VOIDNULL(chunkFrom);

    auto allocationCountBefore = pnc_allocation_count;
    auto* chunkTo = new PNC::Chunk(&fix.Data->StructureABVW, kSize_NodeCapacity, kSize_NodeCount);
    TEST_VALID_CHUNK_STRUCTDATA(chunkTo, kSize_NodeCount, kSize_NodeCapacity);

    ResetCallCounter();
    *chunkTo = std::move(*chunkFrom);
    UTEST_EQUAL(TEXT("Allocation count"), pnc_allocation_count - allocationCountBefore, 0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),        CallCounter::Instance.B.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),         CallCounter::Instance.B.Dtor,       kSize_NodeCount);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),   CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),   CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),    CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),    CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),       CallCounter::Instance.W.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),        CallCounter::Instance.W.Dtor,       kSize_1);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),  CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),  CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),   CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),   CallCounter::Instance.W.MoveAssign, kSize_0);
    TEST_VALID_CHUNK_VOIDNULL(chunkTo);
    TEST_VALID_CHUNK_VOIDNULL(chunkFrom);

    delete chunkTo;
    delete chunkFrom;

    FIXEND;
}

// TODO Chunk.MoveAssignment-VoidNull-VoidData
// 
// TODO Chunk.ConstructChunkPointer-StructData (construct a Chunk copy of a ChunkPointer)
// TODO Chunk.ConstructChunkPointer-VoidNull
// TODO Chunk.ConstructChunkPointer-StructNull
// TODO Chunk.ConstructChunkPointer-VoidData Fails
IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Chunk_CopyConstruction_VoidNull, "Pnc.2-Chunk.3-CopyConstruction-VoidNull", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Chunk_CopyConstruction_VoidNull::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);
    auto* chunkFrom = new PNC::Chunk();
    TEST_VALID_CHUNK_VOIDNULL(chunkFrom);

    ResetCallCounter();
    auto* chunkTo = new PNC::Chunk(*chunkFrom);
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),        CallCounter::Instance.B.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),         CallCounter::Instance.B.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),   CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),   CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),    CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),    CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),       CallCounter::Instance.W.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),        CallCounter::Instance.W.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),  CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),  CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),   CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),   CallCounter::Instance.W.MoveAssign, kSize_0);
    TEST_VALID_CHUNK_VOIDNULL(chunkTo);

    delete chunkTo;
    delete chunkFrom;

    FIXEND;
}
IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Chunk_CopyConstruction_StructData, "Pnc.2-Chunk.3-CopyConstruction-StructData", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Chunk_CopyConstruction_StructData::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);
    auto* chunkFrom = new PNC::Chunk(&fix.Data->StructureABVW, kSize_NodeCapacity, kSize_NodeCount);
    TEST_VALID_CHUNK_STRUCTDATA(chunkFrom, kSize_NodeCount, kSize_NodeCapacity);

    // Set data to copy from with a known value to test the copy.
    WRITE_COMPONENT(chunkFrom, Fix::A, kSize_NodeCount, kTestWrintingValue);
    WRITE_COMPONENT(chunkFrom, Fix::B, kSize_NodeCount, kTestWrintingValue);
    WRITE_COMPONENT(chunkFrom, Fix::V, kSize_1,         kTestWrintingValue);
    WRITE_COMPONENT(chunkFrom, Fix::W, kSize_1,         kTestWrintingValue);

    ResetCallCounter();
    auto* chunkTo = new PNC::Chunk(*chunkFrom);
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),        CallCounter::Instance.B.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),         CallCounter::Instance.B.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),   CallCounter::Instance.B.CopyCtor,   kSize_NodeCount);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),   CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),    CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),    CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),       CallCounter::Instance.W.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),        CallCounter::Instance.W.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),  CallCounter::Instance.W.CopyCtor,   kSize_1);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),  CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),   CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),   CallCounter::Instance.W.MoveAssign, kSize_0);
    TEST_VALID_CHUNK_STRUCTDATA(chunkTo, kSize_NodeCount, kSize_NodeCapacity);

    TEST_COMPONENT_VALUE("Copy Construction TrivialNodeComponent",      chunkTo, Fix::A, kSize_NodeCount, kTestWrintingValue);
    TEST_COMPONENT_VALUE("Copy Construction NonTrivialNodeComponent",   chunkTo, Fix::B, kSize_NodeCount, kTestWrintingValue);
    TEST_COMPONENT_VALUE("Copy Construction TrivialChunkComponent",     chunkTo, Fix::V, kSize_1,         kTestWrintingValue);
    TEST_COMPONENT_VALUE("Copy Construction NonTrivialChunkComponent",  chunkTo, Fix::W, kSize_1,         kTestWrintingValue);

    delete chunkTo;
    delete chunkFrom;

    FIXEND;
}



// Copy to chunk with enough space
// Copy to chunk without enough space

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Chunk_CopyAssignment_Self, "Pnc.2-Chunk.2-CopyAssignment-Self", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Chunk_CopyAssignment_Self::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);

    auto* chunkFromAndTo = new PNC::Chunk(&fix.Data->StructureABVW, kSize_NodeCapacity, kSize_NodeCount);
    TEST_VALID_CHUNK_STRUCTDATA(chunkFromAndTo, kSize_NodeCount, kSize_NodeCapacity);

    auto allocationCountBefore = pnc_allocation_count;
    ResetCallCounter();
    *chunkFromAndTo = *chunkFromAndTo;
    UTEST_EQUAL(TEXT("Allocation count"), pnc_allocation_count - allocationCountBefore, 0);
    TEST_VALID_CHUNK_STRUCTDATA(chunkFromAndTo, kSize_NodeCount, kSize_NodeCapacity);
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),        CallCounter::Instance.B.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),         CallCounter::Instance.B.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),   CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),   CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),    CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),    CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),       CallCounter::Instance.W.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),        CallCounter::Instance.W.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),  CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),  CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),   CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),   CallCounter::Instance.W.MoveAssign, kSize_0);

    delete chunkFromAndTo;

    FIXEND;
}
IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Chunk_CopyAssignment_VoidNull_StructData, "Pnc.2-Chunk.4-CopyAssignment-VoidNull-StructData", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Chunk_CopyAssignment_VoidNull_StructData::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);
    auto* chunkFrom = new PNC::Chunk(&fix.Data->StructureABVW, kSize_NodeCapacity, kSize_NodeCount);
    TEST_VALID_CHUNK_STRUCTDATA(chunkFrom, kSize_NodeCount, kSize_NodeCapacity);

    // Set data to copy from with a known value to test the copy.
    WRITE_COMPONENT(chunkFrom, Fix::A, kSize_NodeCount, kTestWrintingValue);
    WRITE_COMPONENT(chunkFrom, Fix::B, kSize_NodeCount, kTestWrintingValue);
    WRITE_COMPONENT(chunkFrom, Fix::V, kSize_1,         kTestWrintingValue);
    WRITE_COMPONENT(chunkFrom, Fix::W, kSize_1,         kTestWrintingValue);

    auto* chunkTo = new PNC::Chunk();
    TEST_VALID_CHUNK_VOIDNULL(chunkTo);

    ResetCallCounter();
    *chunkTo = *chunkFrom;
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),        CallCounter::Instance.B.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),         CallCounter::Instance.B.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),   CallCounter::Instance.B.CopyCtor,   kSize_NodeCount);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),   CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),    CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),    CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),       CallCounter::Instance.W.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),        CallCounter::Instance.W.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),  CallCounter::Instance.W.CopyCtor,   kSize_1);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),  CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),   CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),   CallCounter::Instance.W.MoveAssign, kSize_0);
    TEST_VALID_CHUNK_STRUCTDATA(chunkTo, kSize_NodeCount, kSize_NodeCapacity);
    UTEST_TRUE(TEXT("ChunkTo is not the same data as ChunkFrom"), !PNC::ChunkPointer::IsSameData(*chunkTo, *chunkFrom));

    TEST_COMPONENT_VALUE("Copy Assignment TrivialNodeComponent",      chunkTo, Fix::A, kSize_NodeCount, kTestWrintingValue);
    TEST_COMPONENT_VALUE("Copy Assignment NonTrivialNodeComponent",   chunkTo, Fix::B, kSize_NodeCount, kTestWrintingValue);
    TEST_COMPONENT_VALUE("Copy Assignment TrivialChunkComponent",     chunkTo, Fix::V, kSize_1,         kTestWrintingValue);
    TEST_COMPONENT_VALUE("Copy Assignment NonTrivialChunkComponent",  chunkTo, Fix::W, kSize_1,         kTestWrintingValue);

    delete chunkTo;
    delete chunkFrom;

    FIXEND;
}
IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Chunk_CopyAssignment_StructData_VoidNull, "Pnc.2-Chunk.4-CopyAssignment-StructData-VoidNull", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Chunk_CopyAssignment_StructData_VoidNull::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);
    auto* chunkFrom = new PNC::Chunk();
    TEST_VALID_CHUNK_VOIDNULL(chunkFrom);

    auto allocationCountBefore = pnc_allocation_count;
    auto* chunkTo = new PNC::Chunk(&fix.Data->StructureABVW, kSize_NodeCapacity, kSize_NodeCount);
    TEST_VALID_CHUNK_STRUCTDATA(chunkTo, kSize_NodeCount, kSize_NodeCapacity);

    ResetCallCounter();
    *chunkTo = *chunkFrom;
    UTEST_EQUAL(TEXT("Allocation count"), pnc_allocation_count - allocationCountBefore, 0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),         CallCounter::Instance.B.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),          CallCounter::Instance.B.Dtor,       kSize_NodeCount);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),    CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),    CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),     CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),     CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),        CallCounter::Instance.W.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),         CallCounter::Instance.W.Dtor,       kSize_1);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),   CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),   CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),    CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),    CallCounter::Instance.W.MoveAssign, kSize_0);
    TEST_VALID_CHUNK_VOIDNULL(chunkTo);

    delete chunkTo;
    delete chunkFrom;

    FIXEND;
}





//
IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Chunk_AddNode, "Pnc.2-Chunk.9-AddNode", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Chunk_AddNode::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);

    ResetCallCounter();
    auto* chunk = new PNC::Chunk(&fix.Data->StructureABVW, kSize_NodeCapacity, 0);
    TEST_VALID_CHUNK_STRUCTDATA(chunk, 0, kSize_NodeCapacity);
    UTEST_EQUAL(TEXT("Available Nodes"), chunk->AvailableNodes(), kSize_NodeCapacity);
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),         CallCounter::Instance.B.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),          CallCounter::Instance.B.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),    CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),    CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),     CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),     CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),        CallCounter::Instance.W.Ctor,       kSize_1);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),         CallCounter::Instance.W.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),   CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),   CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),    CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),    CallCounter::Instance.W.MoveAssign, kSize_0);

    auto allocationCountBefore = pnc_allocation_count;
    ResetCallCounter();
    PNC::Size_t index = chunk->AddNodes(kSize_NodeCapacity);
    UTEST_EQUAL(TEXT("Added Node Index"), index, 0);
    UTEST_EQUAL(TEXT("Allocation count"), pnc_allocation_count - allocationCountBefore, 0);
    TEST_VALID_CHUNK_STRUCTDATA(chunk, kSize_NodeCapacity, kSize_NodeCapacity);
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),         CallCounter::Instance.B.Ctor,       kSize_NodeCapacity);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),          CallCounter::Instance.B.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),    CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),    CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),     CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),     CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),        CallCounter::Instance.W.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),         CallCounter::Instance.W.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),   CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),   CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),    CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),    CallCounter::Instance.W.MoveAssign, kSize_0);

    ResetCallCounter();
    delete chunk;
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),         CallCounter::Instance.B.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),          CallCounter::Instance.B.Dtor,       kSize_NodeCapacity);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),    CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),    CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),     CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),     CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),        CallCounter::Instance.W.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),         CallCounter::Instance.W.Dtor,       kSize_1);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),   CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),   CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),    CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),    CallCounter::Instance.W.MoveAssign, kSize_0);
    FIXEND;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Chunk_RemoveNode_All, "Pnc.2-Chunk.9-RemoveNode-All", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Chunk_RemoveNode_All::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);
    ResetCallCounter();
    auto* chunk = new PNC::Chunk(&fix.Data->StructureABVW, kSize_NodeCapacity, kSize_NodeCapacity);
    TEST_VALID_CHUNK_STRUCTDATA(chunk, kSize_NodeCapacity, kSize_NodeCapacity);
    UTEST_EQUAL(TEXT("Available Nodes"), chunk->AvailableNodes(), 0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),         CallCounter::Instance.B.Ctor,       kSize_NodeCapacity);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),          CallCounter::Instance.B.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),    CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),    CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),     CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),     CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),        CallCounter::Instance.W.Ctor,       kSize_1);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),         CallCounter::Instance.W.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),   CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),   CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),    CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),    CallCounter::Instance.W.MoveAssign, kSize_0);

    auto allocationCountBefore = pnc_allocation_count;
    ResetCallCounter();
    chunk->RemoveNode(0, kSize_NodeCapacity);
    UTEST_EQUAL(TEXT("Allocation count"), pnc_allocation_count - allocationCountBefore, 0);
    TEST_VALID_CHUNK_STRUCTDATA(chunk, kSize_0, kSize_NodeCapacity);
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),         CallCounter::Instance.B.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),          CallCounter::Instance.B.Dtor,       kSize_NodeCapacity);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),    CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),    CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),     CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),     CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),        CallCounter::Instance.W.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),         CallCounter::Instance.W.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),   CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),   CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),    CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),    CallCounter::Instance.W.MoveAssign, kSize_0);

    ResetCallCounter();
    delete chunk;
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),         CallCounter::Instance.B.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),          CallCounter::Instance.B.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),    CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),    CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),     CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),     CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),        CallCounter::Instance.W.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),         CallCounter::Instance.W.Dtor,       kSize_1);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),   CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),   CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),    CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),    CallCounter::Instance.W.MoveAssign, kSize_0);
    FIXEND;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Chunk_RemoveNode_Midsection, "Pnc.2-Chunk.9-RemoveNode-Midsection", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Chunk_RemoveNode_Midsection::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);
    ResetCallCounter();
    auto* chunk = new PNC::Chunk(&fix.Data->StructureABVW, kSize_NodeCapacity, kSize_NodeCapacity);
    TEST_VALID_CHUNK_STRUCTDATA(chunk, kSize_NodeCapacity, kSize_NodeCapacity);
    UTEST_EQUAL(TEXT("Available Nodes"), chunk->AvailableNodes(), 0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),         CallCounter::Instance.B.Ctor,       kSize_NodeCapacity);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),          CallCounter::Instance.B.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),    CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),    CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),     CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),     CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),        CallCounter::Instance.W.Ctor,       kSize_1);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),         CallCounter::Instance.W.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),   CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),   CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),    CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),    CallCounter::Instance.W.MoveAssign, kSize_0);

    auto allocationCountBefore = pnc_allocation_count;
    ResetCallCounter();
    chunk->RemoveNode(kSize_NodeCapacityMidStart, kSize_NodeCapacityMidCount);
    UTEST_EQUAL(TEXT("Allocation count"), pnc_allocation_count - allocationCountBefore, 0);
    TEST_VALID_CHUNK_STRUCTDATA(chunk, kSize_NodeCapacity - kSize_NodeCapacityMidCount, kSize_NodeCapacity);
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),         CallCounter::Instance.B.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),          CallCounter::Instance.B.Dtor,       kSize_NodeCapacityMidCount);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),    CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),    CallCounter::Instance.B.MoveCtor,   kSize_NodeCapacity - (kSize_NodeCapacityMidStart + kSize_NodeCapacityMidCount));
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),     CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),     CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),        CallCounter::Instance.W.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),         CallCounter::Instance.W.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),   CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),   CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),    CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),    CallCounter::Instance.W.MoveAssign, kSize_0);
    // TODO Test if node data has moved
    ResetCallCounter();
    delete chunk;
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),         CallCounter::Instance.B.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),          CallCounter::Instance.B.Dtor,       kSize_NodeCapacity - kSize_NodeCapacityMidCount);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),    CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),    CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),     CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),     CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),        CallCounter::Instance.W.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),         CallCounter::Instance.W.Dtor,       kSize_1);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),   CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),   CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),    CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),    CallCounter::Instance.W.MoveAssign, kSize_0);
    FIXEND;
}







//
//IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Chunk_CopyAssignment_TrivialNodeComponent, "Pnc.2Chunk.2CopyAssignment.TrivialNodeComponent", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
//bool TestPnc_Chunk_CopyAssignment_TrivialNodeComponent::RunTest(const FString& Parameters)
//{
//    FIXSTART(Fix);
//    auto* chunkFrom = new PNC::Chunk(&fix.Data->StructureA, kSize_NodeCapacity, kSize_NodeCount);
//    TEST_VALID_CHUNK_STRUCTDATA(chunkFrom, kSize_NodeCount, kSize_NodeCapacity);
//
//    // Set data to copy from with a known value to test the copy.
//    WRITE_COMPONENT(chunkFrom, Fix::A, kSize_NodeCount, kTestWrintingValue);
//
//    auto* chunkTo = new PNC::Chunk(&fix.Data->StructureA, kSize_NodeCapacity, kSize_NodeCount);
//    TEST_VALID_CHUNK_STRUCTDATA(chunkTo, kSize_NodeCount, kSize_NodeCapacity);
//    
//    // Copy assign
//    *chunkTo = *chunkFrom;
//    TEST_VALID_CHUNK_STRUCTDATA(chunkTo, kSize_NodeCount, kSize_NodeCapacity);
//    UTEST_TRUE(TEXT("ChunkTo is not the same data as ChunkFrom"), !PNC::ChunkPointer::IsSameData(*chunkTo, *chunkFrom));
//    TEST_COMPONENT_VALUE("Copy Construction", chunkTo, Fix::A, kSize_NodeCount, kTestWrintingValue);
//
//    delete chunkTo;
//    delete chunkFrom;
//    
//    FIXEND;
//}
//IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Chunk_CopyAssignment_TrivialChunkComponent, "Pnc.2Chunk.2CopyAssignment.TrivialChunkComponent", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
//bool TestPnc_Chunk_CopyAssignment_TrivialChunkComponent::RunTest(const FString& Parameters)
//{
//    FIXSTART(Fix);
//    auto* chunkFrom = new PNC::Chunk(&fix.Data->StructureV, kSize_NodeCapacity, kSize_NodeCount);
//    TEST_VALID_CHUNK_STRUCTDATA(chunkFrom, kSize_NodeCount, kSize_NodeCapacity);
//
//    auto* componentDataVFrom = chunkFrom->GetComponentData<Fix::V>();
//    UTEST_TRUE(TEXT("ChunkFrom has ChunkComponent V"), !!componentDataVFrom);
//
//    // Set data to copy from with a known value to test the copy.
//    componentDataVFrom[0].Value = kTestWrintingValue;
//
//    auto* chunkTo = new PNC::Chunk(&fix.Data->StructureV, kSize_NodeCapacity, kSize_NodeCount);
//    TEST_VALID_CHUNK_STRUCTDATA(chunkTo, kSize_NodeCount, kSize_NodeCapacity);
//
//    // Copy assign
//    *chunkTo = *chunkFrom;
//    TEST_VALID_CHUNK_STRUCTDATA(chunkTo, kSize_NodeCount, kSize_NodeCapacity);
//    UTEST_TRUE(TEXT("ChunkTo is not the same data as ChunkFrom"), !PNC::ChunkPointer::IsSameData(*chunkTo, *chunkFrom));
//    
//    auto* componentDataVTo = chunkTo->GetComponentData<Fix::V>();
//    UTEST_TRUE(TEXT("ChunkTo has Chunk Component V"), !!componentDataVTo);
//
//    UTEST_EQUAL(TEXT("Data for ChunkComponent V must be copied"), componentDataVTo[0].Value, kTestWrintingValue);
//
//    delete chunkTo;
//    delete chunkFrom;
//    
//    FIXEND;
//}
//
//IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Chunk_CopyAssignment_NonTrivialNodeComponent, "Pnc.2Chunk.2CopyAssignment.NonTrivialNodeComponent", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
//bool TestPnc_Chunk_CopyAssignment_NonTrivialNodeComponent::RunTest(const FString& Parameters)
//{
//    FIXSTART(Fix);
//    auto* chunkFrom = new PNC::Chunk(&fix.Data->StructureB, kSize_NodeCapacity, kSize_NodeCount);
//    TEST_VALID_CHUNK_STRUCTDATA(chunkFrom, kSize_NodeCount, kSize_NodeCapacity);
//
//    auto* componentDataBFrom = chunkFrom->GetComponentData<Fix::B>();
//    UTEST_TRUE(TEXT("ChunkFrom has NodeComponent B"), !!componentDataBFrom);
//
//    // Overwrite data to copy from with different value so it copies over the kTestConstructingValue set by the default constructor.
//    for (PNC::Size_t i = 0; i < kSize_NodeCount; ++i)
//        componentDataBFrom[i].Value = kTestWrintingValue;
//
//    auto* chunkTo = new PNC::Chunk(&fix.Data->StructureB, kSize_NodeCapacity, kSize_NodeCount);
//    TEST_VALID_CHUNK_STRUCTDATA(chunkTo, kSize_NodeCount, kSize_NodeCapacity);
//
//    // Copy assign
//    *chunkTo = *chunkFrom;
//    TEST_VALID_CHUNK_STRUCTDATA(chunkTo, kSize_NodeCount, kSize_NodeCapacity);
//    UTEST_TRUE(TEXT("ChunkTo is not the same data as ChunkFrom"), !PNC::ChunkPointer::IsSameData(*chunkTo, *chunkFrom));
//
//    auto* componentDataBTo = chunkTo->GetComponentData<Fix::B>();
//    UTEST_TRUE(TEXT("ChunkTo has NodeComponent B"), !!componentDataBTo);
//
//    for (PNC::Size_t i = 0; i < kSize_NodeCount; ++i)
//        UTEST_EQUAL(TEXT("Data for NodeComponent B must be copied"), componentDataBTo[i].Value, kTestWrintingValue);
//
//
//    // Copy assign
//    ResetCallCounter();
//    *chunkTo = *chunkFrom;
//    UTEST_EQUAL(TEXT("Calls to Component B constructor"),       CallCounter::Instance.B.Ctor,       kSize_0);
//    UTEST_EQUAL(TEXT("Calls to Component B destructor"),        CallCounter::Instance.B.Dtor,       kSize_NodeCount);
//    UTEST_EQUAL(TEXT("Calls to Component B copy constructor"),  CallCounter::Instance.B.CopyCtor,   kSize_NodeCount);
//    UTEST_EQUAL(TEXT("Calls to Component B move constructor"),  CallCounter::Instance.B.MoveCtor,   kSize_0);
//    UTEST_EQUAL(TEXT("Calls to Component B copy assignment"),   CallCounter::Instance.B.CopyAssign, kSize_0);
//    UTEST_EQUAL(TEXT("Calls to Component B move assignment"),   CallCounter::Instance.B.MoveAssign, kSize_0);
//    TEST_VALID_CHUNK_STRUCTDATA(chunkTo, kSize_NodeCount, kSize_NodeCapacity);
//    UTEST_TRUE(TEXT("ChunkTo is not the same data as ChunkFrom"), !PNC::ChunkPointer::IsSameData(*chunkTo, *chunkFrom));
//
//    componentDataBTo = chunkTo->GetComponentData<Fix::B>();
//    UTEST_TRUE(TEXT("ChunkTo has NodeComponent B"), !!componentDataBTo);
//
//    for (PNC::Size_t i = 0; i < kSize_NodeCount; ++i)
//        UTEST_EQUAL(TEXT("Data for NodeComponent B must be copied"), componentDataBTo[i].Value, kTestWrintingValue);
//
//    delete chunkTo;
//    delete chunkFrom;
//    
//    FIXEND;
//}
//
//IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Chunk_CopyAssignment_NonTrivialChunkComponent, "Pnc.2Chunk.2CopyAssignment.NonTrivialChunkComponent", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
//bool TestPnc_Chunk_CopyAssignment_NonTrivialChunkComponent::RunTest(const FString& Parameters)
//{
//    FIXSTART(Fix);
//    auto* chunkFrom = new PNC::Chunk(&fix.Data->StructureW, kSize_NodeCapacity, kSize_NodeCount);
//    TEST_VALID_CHUNK_STRUCTDATA(chunkFrom, kSize_NodeCount, kSize_NodeCapacity);
//
//    auto* componentDataWFrom = chunkFrom->GetComponentData<Fix::W>();
//    UTEST_TRUE(TEXT("ChunkFrom has ChunkComponent W"), !!componentDataWFrom);
//
//    // Overwrite data to copy from with different value so it copies over the kTestConstructingValue set by the default constructor.
//    componentDataWFrom[0].Value = kTestWrintingValue;
//
//    auto* chunkTo = new PNC::Chunk(&fix.Data->StructureW, kSize_NodeCapacity, kSize_NodeCount);
//    TEST_VALID_CHUNK_STRUCTDATA(chunkTo, kSize_NodeCount, kSize_NodeCapacity);
//
//    // Copy assign
//    ResetCallCounter();
//    *chunkTo = *chunkFrom;
//    UTEST_EQUAL(TEXT("Calls to Component W constructor"),       CallCounter::Instance.W.Ctor,       kSize_0);
//    UTEST_EQUAL(TEXT("Calls to Component W destructor"),        CallCounter::Instance.W.Dtor,       kSize_1);
//    UTEST_EQUAL(TEXT("Calls to Component W copy constructor"),  CallCounter::Instance.W.CopyCtor,   kSize_1);
//    UTEST_EQUAL(TEXT("Calls to Component W move constructor"),  CallCounter::Instance.W.MoveCtor,   kSize_0);
//    UTEST_EQUAL(TEXT("Calls to Component W copy assignment"),   CallCounter::Instance.W.CopyAssign, kSize_0);
//    UTEST_EQUAL(TEXT("Calls to Component W move assignment"),   CallCounter::Instance.W.MoveAssign, kSize_0);
//    TEST_VALID_CHUNK_STRUCTDATA(chunkTo, kSize_NodeCount, kSize_NodeCapacity);
//    UTEST_TRUE(TEXT("ChunkTo is not the same data as ChunkFrom"), !PNC::ChunkPointer::IsSameData(*chunkTo, *chunkFrom));
//
//    auto* componentDataWTo = chunkTo->GetComponentData<Fix::W>();
//    UTEST_TRUE(TEXT("ChunkTo has ChunkComponent W"), !!componentDataWTo);
//    UTEST_EQUAL(TEXT("Data for ChunkComponent W must be copied"), componentDataWTo[0].Value, kTestWrintingValue);
//
//    delete chunkTo;
//    delete chunkFrom;
//    
//    FIXEND;
//}

//
//IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPncChunkArrayNew, "Pnc.2ChunkArray.0NewA", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
//bool TestPncChunkArrayNew::RunTest(const FString& Parameters)
//{
//    FIXSTART(Fix);
//    delete new PNC::ChunkArray(&fix.Data->StructureA, kSize_NodeCapacity, kSize_ChunkCapacity, kSize_ChunkCount0, kSize_NodeCount0);
//    
//    FIXEND;
//}


//
//
//IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPncChunkAddNode, "Pnc.2Chunk.1AddNode", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
//bool TestPncChunkAddNode::RunTest(const FString& Parameters)
//{
//    FixChunk fix;
//    auto nodeIndex = fix.Chunk->AddNode();
//    
//    return fix.Finalize(*this);
//}
//
//
//IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPncChunkCopy, "Pnc.2Chunk.Copy", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
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