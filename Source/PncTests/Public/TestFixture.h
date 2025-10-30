#pragma once
#include "Common.h"

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


constexpr int kTestConstructingValue = 99;
constexpr int kTestWrintingValue = 50;
constexpr PNC::Size_t kSize_NodeCapacity = 16;
constexpr PNC::Size_t kSize_NodeCapacityBeginStart = 0;
constexpr PNC::Size_t kSize_NodeCapacityBeginCount = 7;
constexpr PNC::Size_t kSize_NodeCapacityMidStart = 5;
constexpr PNC::Size_t kSize_NodeCapacityMidCount = 5;
constexpr PNC::Size_t kSize_NodeCapacityEndStart = 13;
constexpr PNC::Size_t kSize_NodeCapacityEndCount = 3;
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

void ResetCallCounter();
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

using Data = PncTestData;
using Fix = PncTestFixture;