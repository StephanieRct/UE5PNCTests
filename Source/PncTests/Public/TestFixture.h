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

#define TEST_VALID_CHUNKPOINTER_VOIDNULL(chunkPointer) \
    do{\
        auto& _chunkPointer = chunkPointer;\
        UTEST_TRUE(TEXT(#chunkPointer " is VoidNull"), _chunkPointer.IsVoidNull());\
        UTEST_EQUAL(TEXT("VoidNull Chunk '" #chunkPointer "' NodeCount"), _chunkPointer.GetNodeCount(), kSize_0)\
    }while(0)

#define TEST_VALID_CHUNKPOINTER_STRUCTDATA(chunkPointer)\
    do{\
        auto& _chunkPointer = chunkPointer;\
        UTEST_TRUE(TEXT("Chunk is StructData"), _chunkPointer.IsStructData());\
        auto& _internalChunkPointer = Ni::Containers::NChunkPointer::GetInternalChunk(_chunkPointer);\
        auto componentTypeCount = _internalChunkPointer.Structure->GetComponentCount();\
        UTEST_TRUE(TEXT("Chunk owns its ComponentData array"), pnc_owns(_internalChunkPointer.ComponentDataArray, componentTypeCount));\
        for (Ni::Containers::Size_t _i = 0; _i < componentTypeCount; ++_i)\
        {\
            const auto* componentType = _internalChunkPointer.Structure->Components[_i];\
            uint8* begin = (uint8*)_internalChunkPointer.ComponentDataArray[_i];\
            Ni::Containers::Size_t size = 0;\
            switch (componentType->GetOwner())\
            {\
            case Ni::Containers::ComponentOwner::Node:\
                size = _internalChunkPointer.NodeCount * componentType->GetSize();\
                break;\
            case Ni::Containers::ComponentOwner::Chunk:\
                size = componentType->GetSize();\
                break;\
            default:\
                pnc_assert_no_entry_return(false);\
            }\
            UTEST_TRUE(TEXT("Chunk has valid ComponentData Memory"), pnc_owns(begin, size));\
        }\
    }while(0)

#define TEST_VALID_CHUNKPOINTER_STRUCTDATA_N(chunkPointer, nodeCount)\
    do {\
        auto& _chunkPointerN = chunkPointer;\
        TEST_VALID_CHUNKPOINTER_STRUCTDATA(_chunkPointerN);\
        UTEST_EQUAL(TEXT("Chunk's Node Count"), _chunkPointerN.GetNodeCount(), nodeCount);\
    }while (0)



#define TEST_VALID_BUCKETPOINTER_STRUCTDATA(chunk, nodeCount, nodeCapacity)\
    do{\
        auto& _Bucket = chunk;\
        TEST_VALID_CHUNKPOINTER_STRUCTDATA_N(_Bucket, nodeCount);\
        UTEST_EQUAL(TEXT("Chunk's Node Capacity"), _Bucket.GetNodeCapacity(), nodeCapacity);\
    }while(0)

#define TEST_VALID_BUNCHPOINTER_STRUCTDATA(chunk, nodeCount, nodeCapacity)\
    TEST_VALID_BUCKETPOINTER_STRUCTDATA(chunk, nodeCount, nodeCapacity)

#define TEST_VALID_UNIFORMCHUNKARRAY_STRUCTDATA(uniformChunkArray, chunkCount, nodeCountPerChunk)\
    do{\
        auto& _uniformChunkArray = uniformChunkArray;\
        TEST_VALID_CHUNKPOINTER_STRUCTDATA_N(_uniformChunkArray, chunkCount * nodeCountPerChunk);\
        UTEST_EQUAL(TEXT("UniformChunkArray's Chunk Count"),       _uniformChunkArray.GetChunkCount(),    chunkCount);\
        auto& _internalChunkArray = Ni::Containers::NUniformArray::GetInternalChunk(_uniformChunkArray);\
        for (Ni::Containers::Size_t _k = 0; _k < _uniformChunkArray.GetChunkCount(); ++_k)\
        {\
            TEST_VALID_CHUNKPOINTER_STRUCTDATA_N(_uniformChunkArray.GetChunk(_k), nodeCountPerChunk);\
            TEST_VALID_CHUNKPOINTER_STRUCTDATA_N(_uniformChunkArray[_k], nodeCountPerChunk);\
        }\
    }while(0)


#define TEST_VALID_CHUNKARRAY_STRUCTDATA(chunkArray, chunkCount, nodeCount)\
    do{\
        auto& _chunkArray = chunkArray;\
        UTEST_TRUE (TEXT("ChunkArray is StructData"),       _chunkArray.IsStructData());\
        UTEST_EQUAL(TEXT("ChunkArray's Chunk Count"),       _chunkArray.GetChunkCount(),    chunkCount);\
        UTEST_EQUAL(TEXT("ChunkArray's Node Count"),       _chunkArray.GetNodeCount(),    nodeCount);\
        auto& _internalChunkArray = Ni::Containers::NArrayPointer::GetInternalChunk(_chunkArray);\
        UTEST_TRUE(TEXT("ChunkArray owns its ChunkPointer array"), pnc_owns(_internalChunkArray.Array.Chunks, sizeof(Ni::Containers::NArrayPointer::ChunkPointerElement_t) * chunkCount));\
        for (Ni::Containers::Size_t _k = 0; _k < _chunkArray.GetChunkCount(); ++_k)\
        {\
            TEST_VALID_CHUNKPOINTER_STRUCTDATA(_chunkArray.GetChunk(_k));\
        }\
    }while(0)


#define WRITE_COMPONENT(chunk, ComponentType, count, value)\
    do{\
        auto& _chunk = chunk;\
        auto* componentData = _chunk.GetComponentData<ComponentType>();\
        UTEST_TRUE(TEXT(#chunk " Has Component " #ComponentType), !!componentData);\
        for (Ni::Containers::Size_t i = 0; i < count; ++i)\
            componentData[i].Value = value;\
    }while(0)

#define TEST_COMPONENT_VALUE(afterWhat, chunk, ComponentType, count, value)\
    do{\
        auto& _chunk = chunk;\
        auto* componentData = _chunk.GetComponentData<ComponentType>();\
        UTEST_TRUE(TEXT(#chunk " Has Component " #ComponentType), !!componentData);\
        for (Ni::Containers::Size_t i = 0; i < count; ++i)\
            UTEST_EQUAL(TEXT("Value after " afterWhat), componentData[i].Value, value);\
    }while(0)

constexpr int kTestConstructingValue = 99;
constexpr int kTestWrintingValue = 50;

constexpr Ni::Containers::Size_t kSize_1 = 1;
constexpr Ni::Containers::Size_t kSize_0 = 0;

constexpr Ni::Containers::Size_t kSize_NodeCapacity = 16; //must be > kSize_NodeCapacityLow
constexpr Ni::Containers::Size_t kSize_NodeCapacityLow = 6; // must be < kSize_NodeCapacity
constexpr Ni::Containers::Size_t kSize_NodeCapacityBeginStart = 0;
constexpr Ni::Containers::Size_t kSize_NodeCapacityBeginCount = 7;
constexpr Ni::Containers::Size_t kSize_NodeCapacityMidStart = 5;
constexpr Ni::Containers::Size_t kSize_NodeCapacityMidCount = 5;
constexpr Ni::Containers::Size_t kSize_NodeCapacityEndStart = 13;
constexpr Ni::Containers::Size_t kSize_NodeCapacityEndCount = 3;

constexpr Ni::Containers::Size_t kSize_NodeCount = 8;  // must be > kSize_NodeCountLow
constexpr Ni::Containers::Size_t kSize_NodeCountLow = 3;  // must be < kSize_NodeCount
constexpr Ni::Containers::Size_t kSize_NodeCount_0 = 0;

constexpr Ni::Containers::Size_t kSize_ChunkCapacity = 12;
constexpr Ni::Containers::Size_t kSize_ChunkCount = 6;
constexpr Ni::Containers::Size_t kSize_ChunkCount_0 = 0;
constexpr Ni::Containers::Size_t kSize_NodeCountPerChunk = kSize_NodeCount;
constexpr Ni::Containers::Size_t kSize_NodeCountPerChunk_0 = 0;
constexpr Ni::Containers::Size_t kSize_NodeCapacityPerChunk = kSize_NodeCapacity;

constexpr Ni::Containers::Size_t kSize_ArrayNodeCapacity = kSize_NodeCapacity * kSize_ChunkCapacity;

struct TypeCallCounter
{
public:
    std::atomic<Ni::Containers::Size_t> Ctor = 0;
    std::atomic<Ni::Containers::Size_t> Dtor = 0;
    std::atomic<Ni::Containers::Size_t> CopyCtor = 0;
    std::atomic<Ni::Containers::Size_t> MoveCtor = 0;
    std::atomic<Ni::Containers::Size_t> CopyAssign = 0;
    std::atomic<Ni::Containers::Size_t> MoveAssign = 0;
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
struct TestNodeComponentA : Ni::Containers::NodeComponent
{
public:
    int Value;
};
struct TestNodeComponentB : Ni::Containers::NodeComponent
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

struct TestChunkComponentV : Ni::Containers::ChunkComponent
{
public:
    int Value;
};
struct TestChunkComponentW : Ni::Containers::ChunkComponent
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

    using NA = TestNodeComponentA;
    using B = TestNodeComponentB;
    using V = TestChunkComponentV;
    using W = TestChunkComponentW;
public:

    Ni::Containers::ComponentType ComponentTypeA;
    Ni::Containers::ComponentType ComponentTypeB;
    Ni::Containers::ComponentType ComponentTypeV;
    Ni::Containers::ComponentType ComponentTypeW;

    Ni::Containers::ChunkStructure StructureA;
    Ni::Containers::ChunkStructure StructureB;
    Ni::Containers::ChunkStructure StructureAB;
    Ni::Containers::ChunkStructure StructureV;
    Ni::Containers::ChunkStructure StructureW;
    Ni::Containers::ChunkStructure StructureVW;
    Ni::Containers::ChunkStructure StructureAV;
    Ni::Containers::ChunkStructure StructureBV;
    Ni::Containers::ChunkStructure StructureBW;
    Ni::Containers::ChunkStructure StructureABV;
    Ni::Containers::ChunkStructure StructureAVW;
    Ni::Containers::ChunkStructure StructureBVW;
    Ni::Containers::ChunkStructure StructureABVW;

    PncTestData()
        : ComponentTypeA((NA*)nullptr)
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
        , StructureBW  (&ComponentTypeB, &ComponentTypeW)
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

    using NA = TestNodeComponentA;
    using NB = TestNodeComponentB;
    using CV = TestChunkComponentV;
    using CW = TestChunkComponentW;

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
        //if (Ni::Containers::MemoryTracker<>::AllocationCount != 0)
        //{
        //    UE_LOG(LogFunctionalTest, Log, TEXT("Remaining allocations (%d) should be 0;"), Ni::Containers::MemoryTracker<>::AllocationCount);
        //}
        return !Failed;
    }
};

using Data = PncTestData;
using Fix = PncTestFixture;



#pragma region Old
#define TEST_VALID_CHUNKCHUNK_UNIFORM_STRUCTDATA(chunkChunk, chunkCount, nodeCountPerChunk)\
    do{\
        auto& _chunkChunk = chunkChunk;\
        UTEST_TRUE(TEXT("ChunkChunk is StructData"),        _chunkChunk.IsStructData());\
        UTEST_EQUAL(TEXT("ChunkChunk's Node Capacity"),     _chunkChunk.GetNodeCount(),        nodeCountPerChunk * chunkCount);\
        UTEST_EQUAL(TEXT("ChunkChunk's Node Capacity"),     _chunkChunk.GetNodeCapacity(),     nodeCountPerChunk * chunkCount);\
        UTEST_EQUAL(TEXT("ChunkChunk's Chunk Count"),       _chunkChunk.GetChunkCount(),       chunkCount);\
        UTEST_EQUAL(TEXT("ChunkChunk's Chunk Capacity"),    _chunkChunk.GetChunkCapacity(),    chunkCount);\
        auto& _internalChunkArray = Ni::Containers::NArrayPointer::GetInternalChunk(_chunkChunk);\
        UTEST_TRUE(TEXT("ChunkChunk owns its ChunkPointer array"), pnc_owns(_internalChunkArray.Array.Chunks, sizeof(Ni::Containers::NArrayPointer::ChunkPointerElement_t) * chunkCount));\
        for (Ni::Containers::Size_t _k = 0; _k < _chunkChunk.GetChunkCount(); ++_k)\
        {\
            TEST_VALID_CHUNKPOINTER_STRUCTDATA_N(_chunkChunk.GetChunk(_k), nodeCountPerChunk);\
        }\
    }while(0)

#pragma endregion