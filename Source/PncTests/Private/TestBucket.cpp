// Fill out your copyright notice in the Description page of Project Settings.


#include "common.h"
#include "TestFixture.h"


//
//struct PncTestFixtureChunk : public PncTestFixture
//{
//public:
//    PNC::Bucket* Bucket;
//    PncTestFixtureChunk()
//        : Bucket(new PNC::Bucket(&Data->StructureA, kSize_NodeCapacity, kSize_NodeCount_0))
//    {
//        ResetCallCounter();
//    }
//    PncTestFixtureChunk(const PNC::ChunkStructure* structure, const PNC::Size_t nodeCapacity, const PNC::Size_t nodeCount)
//        : Bucket(new PNC::Bucket(structure, nodeCapacity, nodeCount))
//    {
//        ResetCallCounter();
//    }
//    ~PncTestFixtureChunk()
//    {
//        delete Bucket;
//    }
//};

//template<typename TChunk>
//bool ChunkIsValidStructData(FAutomationTestBase& test, TChunk* const  chunk, const PNC::Size_t nodeCount, const PNC::Size_t nodeCapacity)
//{
//    if (!test.TestTrue(TEXT("Chunk is allocated"), !!chunk))
//        return false;
//
//    if (!test.TestTrue(TEXT("Chunk is StructData"), chunk->IsStructData()))
//        return false;
//
//    if (!test.TestEqual(TEXT("Chunk's Node Count"), chunk->GetNodeCount(), nodeCount))
//        return false;
//
//    if (!test.TestEqual(TEXT("Chunk's Node Capacity"), chunk->GetNodeCapacity(), nodeCapacity))
//        return false;
//
//    auto& internalChunk = PNC::ChunkPointer::GetInternalChunk(*chunk);
//    auto componentTypeCount = internalChunk.Structure->GetComponentCount();
//
//    if (!test.TestTrue(TEXT("Chunk has valid ComponentDataArray Memory"), pnc_owns(internalChunk.ComponentData, componentTypeCount)))
//        return false;
//    for (PNC::Size_t i = 0; i < componentTypeCount; ++i)
//    {
//        const auto* componentType = internalChunk.Structure->Components[i];
//        uint8* begin = (uint8*) internalChunk.ComponentData[i];
//        PNC::Size_t size = 0;
//
//        switch (componentType->GetOwner())
//        {
//            case PNC::ComponentOwner_Node:
//                size = internalChunk.NodeCount * componentType->GetSize();
//                break;
//            case PNC::ComponentOwner_Chunk:
//                size = componentType->GetSize();
//                break;
//            default:
//                pnc_assert_no_entry_return(false);
//        }
//
//        if (!test.TestTrue(TEXT("Chunk has valid ComponentData Memory"), pnc_owns(begin, size)))
//            return false;
//    }
//}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Bucket_Construct_StructData, "Pnc.3-Bucket.0-Construct-StructData", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Bucket_Construct_StructData::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);
    ResetCallCounter();
    auto* chunk = new PNC::Bucket(&fix.Data->StructureABVW, kSize_NodeCapacity, kSize_NodeCount);
    TEST_VALID_CHUNK_STRUCTDATA(*chunk, kSize_NodeCount, kSize_NodeCapacity);
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

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Bucket_MoveConstruction, "Pnc.3-Bucket.1-MoveConstruction", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Bucket_MoveConstruction::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);
    auto* chunkFrom = new PNC::Bucket(&fix.Data->StructureABVW, kSize_NodeCapacity, kSize_NodeCount);
    TEST_VALID_CHUNK_STRUCTDATA(*chunkFrom, kSize_NodeCount, kSize_NodeCapacity);

    // Set data to copy from with a known value to test the copy.
    WRITE_COMPONENT(*chunkFrom, Fix::A, kSize_NodeCount, kTestWrintingValue);
    WRITE_COMPONENT(*chunkFrom, Fix::B, kSize_NodeCount, kTestWrintingValue);
    WRITE_COMPONENT(*chunkFrom, Fix::V, kSize_1,         kTestWrintingValue);
    WRITE_COMPONENT(*chunkFrom, Fix::W, kSize_1,         kTestWrintingValue);
    
    ResetCallCounter();
    auto allocationCountBefore = pnc_allocation_count;
    auto* chunkTo = new PNC::Bucket(std::move(*chunkFrom));
    
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
    TEST_VALID_CHUNK_STRUCTDATA(*chunkTo, kSize_NodeCount, kSize_NodeCapacity);
    TEST_VALID_CHUNK_VOIDNULL(*chunkFrom);

    TEST_COMPONENT_VALUE("Move Construction TrivialNodeComponent",      *chunkTo, Fix::A, kSize_NodeCount, kTestWrintingValue);
    TEST_COMPONENT_VALUE("Move Construction NonTrivialNodeComponent",   *chunkTo, Fix::B, kSize_NodeCount, kTestWrintingValue);
    TEST_COMPONENT_VALUE("Move Construction TrivialChunkComponent",     *chunkTo, Fix::V, kSize_1,         kTestWrintingValue);
    TEST_COMPONENT_VALUE("Move Construction NonTrivialChunkComponent",  *chunkTo, Fix::W, kSize_1,         kTestWrintingValue);

    delete chunkTo;
    delete chunkFrom;

    FIXEND;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Bucket_MoveAssignment_Self, "Pnc.3-Bucket.2-MoveAssignment-Self", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Bucket_MoveAssignment_Self::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);

    auto* chunkFromAndTo = new PNC::Bucket(&fix.Data->StructureABVW, kSize_NodeCapacity, kSize_NodeCount);
    TEST_VALID_CHUNK_STRUCTDATA(*chunkFromAndTo, kSize_NodeCount, kSize_NodeCapacity);

    auto allocationCountBefore = pnc_allocation_count;
    ResetCallCounter();
    *chunkFromAndTo = std::move(*chunkFromAndTo);
    UTEST_EQUAL(TEXT("Allocation count"), pnc_allocation_count - allocationCountBefore, 0);
    TEST_VALID_CHUNK_STRUCTDATA(*chunkFromAndTo, kSize_NodeCount, kSize_NodeCapacity);
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
IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Bucket_MoveAssignment_VoidNull_StructData, "Pnc.3-Bucket.2-MoveAssignment-VoidNull-StructData", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Bucket_MoveAssignment_VoidNull_StructData::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);
    auto* chunkFrom = new PNC::Bucket(&fix.Data->StructureABVW, kSize_NodeCapacity, kSize_NodeCount);
    TEST_VALID_CHUNK_STRUCTDATA(*chunkFrom, kSize_NodeCount, kSize_NodeCapacity);

    // Set data to copy from with a known value to test the copy.
    WRITE_COMPONENT(*chunkFrom, Fix::A, kSize_NodeCount, kTestWrintingValue);
    WRITE_COMPONENT(*chunkFrom, Fix::B, kSize_NodeCount, kTestWrintingValue);
    WRITE_COMPONENT(*chunkFrom, Fix::V, kSize_1,         kTestWrintingValue);
    WRITE_COMPONENT(*chunkFrom, Fix::W, kSize_1,         kTestWrintingValue);

    auto* chunkTo = new PNC::Bucket();
    TEST_VALID_CHUNK_VOIDNULL(*chunkTo);

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
    TEST_VALID_CHUNK_STRUCTDATA(*chunkTo, kSize_NodeCount, kSize_NodeCapacity);
    TEST_VALID_CHUNK_VOIDNULL(*chunkFrom);

    TEST_COMPONENT_VALUE("Move Construction TrivialNodeComponent",      *chunkTo, Fix::A, kSize_NodeCount, kTestWrintingValue);
    TEST_COMPONENT_VALUE("Move Construction NonTrivialNodeComponent",   *chunkTo, Fix::B, kSize_NodeCount, kTestWrintingValue);
    TEST_COMPONENT_VALUE("Move Construction TrivialChunkComponent",     *chunkTo, Fix::V, kSize_1,         kTestWrintingValue);
    TEST_COMPONENT_VALUE("Move Construction NonTrivialChunkComponent",  *chunkTo, Fix::W, kSize_1,         kTestWrintingValue);

    delete chunkTo;
    delete chunkFrom;

    FIXEND;
}
IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Bucket_MoveAssignment_StructData_VoidNull, "Pnc.3-Bucket.2-MoveAssignment-StructData-VoidNull", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Bucket_MoveAssignment_StructData_VoidNull::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);

    auto* chunkFrom = new PNC::Bucket();
    TEST_VALID_CHUNK_VOIDNULL(*chunkFrom);

    auto allocationCountBefore = pnc_allocation_count;
    auto* chunkTo = new PNC::Bucket(&fix.Data->StructureABVW, kSize_NodeCapacity, kSize_NodeCount);
    TEST_VALID_CHUNK_STRUCTDATA(*chunkTo, kSize_NodeCount, kSize_NodeCapacity);

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
    TEST_VALID_CHUNK_VOIDNULL(*chunkTo);
    TEST_VALID_CHUNK_VOIDNULL(*chunkFrom);

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
IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Bucket_CopyConstruction_VoidNull, "Pnc.3-Bucket.3-CopyConstruction-VoidNull", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Bucket_CopyConstruction_VoidNull::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);
    auto* chunkFrom = new PNC::Bucket();
    TEST_VALID_CHUNK_VOIDNULL(*chunkFrom);

    ResetCallCounter();
    auto* chunkTo = new PNC::Bucket(*chunkFrom);
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
    TEST_VALID_CHUNK_VOIDNULL(*chunkTo);

    delete chunkTo;
    delete chunkFrom;

    FIXEND;
}
IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Bucket_CopyConstruction_StructData, "Pnc.3-Bucket.3-CopyConstruction-StructData", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Bucket_CopyConstruction_StructData::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);
    auto* chunkFrom = new PNC::Bucket(&fix.Data->StructureABVW, kSize_NodeCapacity, kSize_NodeCount);
    TEST_VALID_CHUNK_STRUCTDATA(*chunkFrom, kSize_NodeCount, kSize_NodeCapacity);

    // Set data to copy from with a known value to test the copy.
    WRITE_COMPONENT(*chunkFrom, Fix::A, kSize_NodeCount, kTestWrintingValue);
    WRITE_COMPONENT(*chunkFrom, Fix::B, kSize_NodeCount, kTestWrintingValue);
    WRITE_COMPONENT(*chunkFrom, Fix::V, kSize_1,         kTestWrintingValue);
    WRITE_COMPONENT(*chunkFrom, Fix::W, kSize_1,         kTestWrintingValue);

    ResetCallCounter();
    auto* chunkTo = new PNC::Bucket(*chunkFrom);
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
    TEST_VALID_CHUNK_STRUCTDATA(*chunkTo, kSize_NodeCount, kSize_NodeCapacity);

    TEST_COMPONENT_VALUE("Copy Construction TrivialNodeComponent",      *chunkTo, Fix::A, kSize_NodeCount, kTestWrintingValue);
    TEST_COMPONENT_VALUE("Copy Construction NonTrivialNodeComponent",   *chunkTo, Fix::B, kSize_NodeCount, kTestWrintingValue);
    TEST_COMPONENT_VALUE("Copy Construction TrivialChunkComponent",     *chunkTo, Fix::V, kSize_1,         kTestWrintingValue);
    TEST_COMPONENT_VALUE("Copy Construction NonTrivialChunkComponent",  *chunkTo, Fix::W, kSize_1,         kTestWrintingValue);

    delete chunkTo;
    delete chunkFrom;

    FIXEND;
}



// Copy to chunk with enough space
// Copy to chunk without enough space

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Bucket_CopyAssignment_Self, "Pnc.3-Bucket.4-CopyAssignment-Self", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Bucket_CopyAssignment_Self::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);

    auto* chunkFromAndTo = new PNC::Bucket(&fix.Data->StructureABVW, kSize_NodeCapacity, kSize_NodeCount);
    TEST_VALID_CHUNK_STRUCTDATA(*chunkFromAndTo, kSize_NodeCount, kSize_NodeCapacity);

    auto allocationCountBefore = pnc_allocation_count;
    ResetCallCounter();
    *chunkFromAndTo = *chunkFromAndTo;
    UTEST_EQUAL(TEXT("Allocation count"), pnc_allocation_count - allocationCountBefore, 0);
    TEST_VALID_CHUNK_STRUCTDATA(*chunkFromAndTo, kSize_NodeCount, kSize_NodeCapacity);
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
IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Bucket_CopyAssignment_VoidNull_StructData, "Pnc.3-Bucket.4-CopyAssignment-VoidNull-StructData", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Bucket_CopyAssignment_VoidNull_StructData::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);
    auto* chunkFrom = new PNC::Bucket(&fix.Data->StructureABVW, kSize_NodeCapacity, kSize_NodeCount);
    TEST_VALID_CHUNK_STRUCTDATA(*chunkFrom, kSize_NodeCount, kSize_NodeCapacity);

    // Set data to copy from with a known value to test the copy.
    WRITE_COMPONENT(*chunkFrom, Fix::A, kSize_NodeCount, kTestWrintingValue);
    WRITE_COMPONENT(*chunkFrom, Fix::B, kSize_NodeCount, kTestWrintingValue);
    WRITE_COMPONENT(*chunkFrom, Fix::V, kSize_1,         kTestWrintingValue);
    WRITE_COMPONENT(*chunkFrom, Fix::W, kSize_1,         kTestWrintingValue);

    auto* chunkTo = new PNC::Bucket();
    TEST_VALID_CHUNK_VOIDNULL(*chunkTo);

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
    TEST_VALID_CHUNK_STRUCTDATA(*chunkTo, kSize_NodeCount, kSize_NodeCapacity);
    UTEST_TRUE(TEXT("ChunkTo is not the same data as ChunkFrom"), !PNC::ChunkPointer::IsSameData(*chunkTo, *chunkFrom));

    TEST_COMPONENT_VALUE("Copy Assignment TrivialNodeComponent",      *chunkTo, Fix::A, kSize_NodeCount, kTestWrintingValue);
    TEST_COMPONENT_VALUE("Copy Assignment NonTrivialNodeComponent",   *chunkTo, Fix::B, kSize_NodeCount, kTestWrintingValue);
    TEST_COMPONENT_VALUE("Copy Assignment TrivialChunkComponent",     *chunkTo, Fix::V, kSize_1,         kTestWrintingValue);
    TEST_COMPONENT_VALUE("Copy Assignment NonTrivialChunkComponent",  *chunkTo, Fix::W, kSize_1,         kTestWrintingValue);

    delete chunkTo;
    delete chunkFrom;

    FIXEND;
}
IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Bucket_CopyAssignment_StructData_VoidNull, "Pnc.3-Bucket.4-CopyAssignment-StructData-VoidNull", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Bucket_CopyAssignment_StructData_VoidNull::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);
    auto* chunkFrom = new PNC::Bucket();
    TEST_VALID_CHUNK_VOIDNULL(*chunkFrom);

    auto allocationCountBefore = pnc_allocation_count;
    auto* chunkTo = new PNC::Bucket(&fix.Data->StructureABVW, kSize_NodeCapacity, kSize_NodeCount);
    TEST_VALID_CHUNK_STRUCTDATA(*chunkTo, kSize_NodeCount, kSize_NodeCapacity);

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
    TEST_VALID_CHUNK_VOIDNULL(*chunkTo);

    delete chunkTo;
    delete chunkFrom;

    FIXEND;
}

//
IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Bucket_AddNode, "Pnc.3-Bucket.5-AddNode", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Bucket_AddNode::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);

    ResetCallCounter();
    auto* chunk = new PNC::Bucket(&fix.Data->StructureABVW, kSize_NodeCapacity, 0);
    TEST_VALID_CHUNK_STRUCTDATA(*chunk, 0, kSize_NodeCapacity);
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
    TEST_VALID_CHUNK_STRUCTDATA(*chunk, kSize_NodeCapacity, kSize_NodeCapacity);
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

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Bucket_RemoveNode_All, "Pnc.3-Bucket.6-RemoveNode-All", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Bucket_RemoveNode_All::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);
    ResetCallCounter();
    auto* chunk = new PNC::Bucket(&fix.Data->StructureABVW, kSize_NodeCapacity, kSize_NodeCapacity);
    TEST_VALID_CHUNK_STRUCTDATA(*chunk, kSize_NodeCapacity, kSize_NodeCapacity);
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
    TEST_VALID_CHUNK_STRUCTDATA(*chunk, kSize_0, kSize_NodeCapacity);
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

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Bucket_RemoveNode_Midsection, "Pnc.3-Bucket.6-RemoveNode-Midsection", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Bucket_RemoveNode_Midsection::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);
    ResetCallCounter();
    auto* chunk = new PNC::Bucket(&fix.Data->StructureABVW, kSize_NodeCapacity, kSize_NodeCapacity);
    TEST_VALID_CHUNK_STRUCTDATA(*chunk, kSize_NodeCapacity, kSize_NodeCapacity);
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

    // Write sequential numbers in component A
    auto* componentDataA = chunk->GetComponentData<Fix::A>(); 
    UTEST_TRUE(TEXT("Has Component componentDataA"), !!componentDataA); 
    for (PNC::Size_t i = 0; i < chunk->GetNodeCount(); ++i)
        componentDataA[i].Value = i; 

    auto allocationCountBefore = pnc_allocation_count;
    ResetCallCounter();
    chunk->RemoveNode(kSize_NodeCapacityMidStart, kSize_NodeCapacityMidCount);
    UTEST_EQUAL(TEXT("Allocation count"), pnc_allocation_count - allocationCountBefore, 0);
    TEST_VALID_CHUNK_STRUCTDATA(*chunk, kSize_NodeCapacity - kSize_NodeCapacityMidCount, kSize_NodeCapacity);
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),         CallCounter::Instance.B.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),          CallCounter::Instance.B.Dtor,       kSize_NodeCapacityMidCount);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),    CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),    CallCounter::Instance.B.MoveCtor,   kSize_NodeCapacityMidCount);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),     CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),     CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),        CallCounter::Instance.W.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),         CallCounter::Instance.W.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),   CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),   CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),    CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),    CallCounter::Instance.W.MoveAssign, kSize_0);

    // Test if node data has moved to the correct position in the chunk
    for (PNC::Size_t i = 0; i < kSize_NodeCapacityMidStart; ++i)
    {
        UTEST_EQUAL(TEXT("componentDataA value"), componentDataA[i].Value, i);
    }
    // Nodes from the end should have moved to the removed nodes
    for (PNC::Size_t i = 0; i < kSize_NodeCapacityMidCount; ++i)
    {
        UTEST_EQUAL(TEXT("componentDataA value"), componentDataA[kSize_NodeCapacityMidStart + i].Value, kSize_NodeCapacity - kSize_NodeCapacityMidCount + i);
    }
    for (PNC::Size_t i = kSize_NodeCapacityMidStart + kSize_NodeCapacityMidCount; i < kSize_NodeCapacity - kSize_NodeCapacityMidCount; ++i)
    {
        UTEST_EQUAL(TEXT("componentDataA value"), componentDataA[i].Value, i);
    }

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

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Bucket_RemoveNode_End, "Pnc.3-Bucket.6-RemoveNode-End", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Bucket_RemoveNode_End::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);
    ResetCallCounter();
    auto* chunk = new PNC::Bucket(&fix.Data->StructureABVW, kSize_NodeCapacity, kSize_NodeCapacity);
    TEST_VALID_CHUNK_STRUCTDATA(*chunk, kSize_NodeCapacity, kSize_NodeCapacity);
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

    // Write sequential numbers in component A
    auto* componentDataA = chunk->GetComponentData<Fix::A>(); 
    UTEST_TRUE(TEXT("Has Component componentDataA"), !!componentDataA); 
    for (PNC::Size_t i = 0; i < chunk->GetNodeCount(); ++i)
        componentDataA[i].Value = i; 

    auto allocationCountBefore = pnc_allocation_count;
    ResetCallCounter();
    chunk->RemoveNode(kSize_NodeCapacityBeginStart, kSize_NodeCapacityBeginCount);
    const PNC::Size_t newNodeCount = kSize_NodeCapacity - kSize_NodeCapacityBeginCount;
    UTEST_EQUAL(TEXT("Allocation count"), pnc_allocation_count - allocationCountBefore, 0);
    TEST_VALID_CHUNK_STRUCTDATA(*chunk, newNodeCount, kSize_NodeCapacity);
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),         CallCounter::Instance.B.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),          CallCounter::Instance.B.Dtor,       kSize_NodeCapacityBeginCount);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),    CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),    CallCounter::Instance.B.MoveCtor,   kSize_NodeCapacityBeginCount);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),     CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),     CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),        CallCounter::Instance.W.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),         CallCounter::Instance.W.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),   CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),   CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),    CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),    CallCounter::Instance.W.MoveAssign, kSize_0);

    // Test if node data has moved to the correct position in the chunk
    for (PNC::Size_t i = 0; i < kSize_NodeCapacityBeginCount; ++i)
    {
        UTEST_EQUAL(TEXT("componentDataA value"), componentDataA[i].Value, kSize_NodeCapacity - kSize_NodeCapacityBeginCount + i);
    }
    for (PNC::Size_t i = kSize_NodeCapacityBeginStart + kSize_NodeCapacityBeginCount; i < kSize_NodeCapacity - kSize_NodeCapacityBeginCount; ++i)
    {
        UTEST_EQUAL(TEXT("componentDataA value"), componentDataA[i].Value, i);
    }


    ResetCallCounter();
    delete chunk;
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),         CallCounter::Instance.B.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),          CallCounter::Instance.B.Dtor,       kSize_NodeCapacity - kSize_NodeCapacityBeginCount);
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

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Bucket_RemoveNodeKeepOrder_Midsection, "Pnc.3-Bucket.6-RemoveNodeKeepOrder-Midsection", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Bucket_RemoveNodeKeepOrder_Midsection::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);
    ResetCallCounter();
    auto* chunk = new PNC::Bucket(&fix.Data->StructureABVW, kSize_NodeCapacity, kSize_NodeCapacity);
    TEST_VALID_CHUNK_STRUCTDATA(*chunk, kSize_NodeCapacity, kSize_NodeCapacity);
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

    // Write sequential numbers in component A
    auto* componentDataA = chunk->GetComponentData<Fix::A>();
    UTEST_TRUE(TEXT("Has Component componentDataA"), !!componentDataA);
    for (PNC::Size_t i = 0; i < chunk->GetNodeCount(); ++i)
        componentDataA[i].Value = i;

    auto allocationCountBefore = pnc_allocation_count;
    ResetCallCounter();
    chunk->RemoveNodeKeepOrder(kSize_NodeCapacityMidStart, kSize_NodeCapacityMidCount);
    UTEST_EQUAL(TEXT("Allocation count"), pnc_allocation_count - allocationCountBefore, 0);
    TEST_VALID_CHUNK_STRUCTDATA(*chunk, kSize_NodeCapacity - kSize_NodeCapacityMidCount, kSize_NodeCapacity);
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
    
    // Test if node data has moved to the correct position in the chunk
    for (PNC::Size_t i = 0; i < kSize_NodeCapacityMidStart; ++i)
    {
        UTEST_EQUAL(TEXT("componentDataA value"), componentDataA[i].Value, i);
    }
    for (PNC::Size_t i = kSize_NodeCapacityMidStart; i < kSize_NodeCapacity - kSize_NodeCapacityMidCount; ++i)
    {
        UTEST_EQUAL(TEXT("componentDataA value"), componentDataA[i].Value, i + kSize_NodeCapacityMidCount);
    }

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

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Bucket_RemoveNodeKeepOrder_End, "Pnc.3-Bucket.6-RemoveNodeKeepOrder-End", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Bucket_RemoveNodeKeepOrder_End::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);
    ResetCallCounter();
    auto* chunk = new PNC::Bucket(&fix.Data->StructureABVW, kSize_NodeCapacity, kSize_NodeCapacity);
    TEST_VALID_CHUNK_STRUCTDATA(*chunk, kSize_NodeCapacity, kSize_NodeCapacity);
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

    // Write sequential numbers in component A
    auto* componentDataA = chunk->GetComponentData<Fix::A>(); 
    UTEST_TRUE(TEXT("Has Component componentDataA"), !!componentDataA); 
    for (PNC::Size_t i = 0; i < chunk->GetNodeCount(); ++i)
        componentDataA[i].Value = i; 

    auto allocationCountBefore = pnc_allocation_count;
    ResetCallCounter();
    chunk->RemoveNodeKeepOrder(kSize_NodeCapacityEndStart, kSize_NodeCapacityEndCount);
    const PNC::Size_t newNodeCount = kSize_NodeCapacity - kSize_NodeCapacityEndCount;
    UTEST_EQUAL(TEXT("Allocation count"), pnc_allocation_count - allocationCountBefore, 0);
    TEST_VALID_CHUNK_STRUCTDATA(*chunk, newNodeCount, kSize_NodeCapacity);
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),         CallCounter::Instance.B.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),          CallCounter::Instance.B.Dtor,       kSize_NodeCapacityEndCount);
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

    // Test if node data has moved to the correct position in the chunk
    for (PNC::Size_t i = 0; i < newNodeCount; ++i)
    {
        UTEST_EQUAL(TEXT("componentDataA value"), componentDataA[i].Value, i);
    }

    ResetCallCounter();
    delete chunk;
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),         CallCounter::Instance.B.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),          CallCounter::Instance.B.Dtor,       kSize_NodeCapacity - kSize_NodeCapacityEndCount);
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

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Bucket_Clear, "Pnc.3-Bucket.7-Clear", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Bucket_Clear::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);
    ResetCallCounter();
    auto* chunk = new PNC::Bucket(&fix.Data->StructureABVW, kSize_NodeCapacity, kSize_NodeCapacity);
    TEST_VALID_CHUNK_STRUCTDATA(*chunk, kSize_NodeCapacity, kSize_NodeCapacity);

    auto allocationCountBefore = pnc_allocation_count;
    ResetCallCounter();
    chunk->Clear();
    UTEST_EQUAL(TEXT("Allocation count"), pnc_allocation_count - allocationCountBefore, 0);
    TEST_VALID_CHUNK_STRUCTDATA(*chunk, 0, kSize_NodeCapacity);
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




//
//IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Bucket_CopyAssignment_TrivialNodeComponent, "Pnc.2Chunk.2CopyAssignment.TrivialNodeComponent", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
//bool TestPnc_Bucket_CopyAssignment_TrivialNodeComponent::RunTest(const FString& Parameters)
//{
//    FIXSTART(Fix);
//    auto* chunkFrom = new PNC::Chunk(&fix.Data->StructureA, kSize_NodeCapacity, kSize_NodeCount);
//    TEST_VALID_CHUNK_STRUCTDATA(*chunkFrom, kSize_NodeCount, kSize_NodeCapacity);
//
//    // Set data to copy from with a known value to test the copy.
//    WRITE_COMPONENT(chunkFrom, Fix::A, kSize_NodeCount, kTestWrintingValue);
//
//    auto* chunkTo = new PNC::Chunk(&fix.Data->StructureA, kSize_NodeCapacity, kSize_NodeCount);
//    TEST_VALID_CHUNK_STRUCTDATA(*chunkTo, kSize_NodeCount, kSize_NodeCapacity);
//    
//    // Copy assign
//    *chunkTo = *chunkFrom;
//    TEST_VALID_CHUNK_STRUCTDATA(*chunkTo, kSize_NodeCount, kSize_NodeCapacity);
//    UTEST_TRUE(TEXT("ChunkTo is not the same data as ChunkFrom"), !PNC::ChunkPointer::IsSameData(*chunkTo, *chunkFrom));
//    TEST_COMPONENT_VALUE("Copy Construction", chunkTo, Fix::A, kSize_NodeCount, kTestWrintingValue);
//
//    delete chunkTo;
//    delete chunkFrom;
//    
//    FIXEND;
//}
//IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Bucket_CopyAssignment_TrivialChunkComponent, "Pnc.2Chunk.2CopyAssignment.TrivialChunkComponent", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
//bool TestPnc_Bucket_CopyAssignment_TrivialChunkComponent::RunTest(const FString& Parameters)
//{
//    FIXSTART(Fix);
//    auto* chunkFrom = new PNC::Chunk(&fix.Data->StructureV, kSize_NodeCapacity, kSize_NodeCount);
//    TEST_VALID_CHUNK_STRUCTDATA(*chunkFrom, kSize_NodeCount, kSize_NodeCapacity);
//
//    auto* componentDataVFrom = chunkFrom->GetComponentData<Fix::V>();
//    UTEST_TRUE(TEXT("ChunkFrom has ChunkComponent V"), !!componentDataVFrom);
//
//    // Set data to copy from with a known value to test the copy.
//    componentDataVFrom[0].Value = kTestWrintingValue;
//
//    auto* chunkTo = new PNC::Chunk(&fix.Data->StructureV, kSize_NodeCapacity, kSize_NodeCount);
//    TEST_VALID_CHUNK_STRUCTDATA(*chunkTo, kSize_NodeCount, kSize_NodeCapacity);
//
//    // Copy assign
//    *chunkTo = *chunkFrom;
//    TEST_VALID_CHUNK_STRUCTDATA(*chunkTo, kSize_NodeCount, kSize_NodeCapacity);
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
//IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Bucket_CopyAssignment_NonTrivialNodeComponent, "Pnc.2Chunk.2CopyAssignment.NonTrivialNodeComponent", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
//bool TestPnc_Bucket_CopyAssignment_NonTrivialNodeComponent::RunTest(const FString& Parameters)
//{
//    FIXSTART(Fix);
//    auto* chunkFrom = new PNC::Chunk(&fix.Data->StructureB, kSize_NodeCapacity, kSize_NodeCount);
//    TEST_VALID_CHUNK_STRUCTDATA(*chunkFrom, kSize_NodeCount, kSize_NodeCapacity);
//
//    auto* componentDataBFrom = chunkFrom->GetComponentData<Fix::B>();
//    UTEST_TRUE(TEXT("ChunkFrom has NodeComponent B"), !!componentDataBFrom);
//
//    // Overwrite data to copy from with different value so it copies over the kTestConstructingValue set by the default constructor.
//    for (PNC::Size_t i = 0; i < kSize_NodeCount; ++i)
//        componentDataBFrom[i].Value = kTestWrintingValue;
//
//    auto* chunkTo = new PNC::Chunk(&fix.Data->StructureB, kSize_NodeCapacity, kSize_NodeCount);
//    TEST_VALID_CHUNK_STRUCTDATA(*chunkTo, kSize_NodeCount, kSize_NodeCapacity);
//
//    // Copy assign
//    *chunkTo = *chunkFrom;
//    TEST_VALID_CHUNK_STRUCTDATA(*chunkTo, kSize_NodeCount, kSize_NodeCapacity);
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
//    TEST_VALID_CHUNK_STRUCTDATA(*chunkTo, kSize_NodeCount, kSize_NodeCapacity);
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
//IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Bucket_CopyAssignment_NonTrivialChunkComponent, "Pnc.2Chunk.2CopyAssignment.NonTrivialChunkComponent", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
//bool TestPnc_Bucket_CopyAssignment_NonTrivialChunkComponent::RunTest(const FString& Parameters)
//{
//    FIXSTART(Fix);
//    auto* chunkFrom = new PNC::Chunk(&fix.Data->StructureW, kSize_NodeCapacity, kSize_NodeCount);
//    TEST_VALID_CHUNK_STRUCTDATA(*chunkFrom, kSize_NodeCount, kSize_NodeCapacity);
//
//    auto* componentDataWFrom = chunkFrom->GetComponentData<Fix::W>();
//    UTEST_TRUE(TEXT("ChunkFrom has ChunkComponent W"), !!componentDataWFrom);
//
//    // Overwrite data to copy from with different value so it copies over the kTestConstructingValue set by the default constructor.
//    componentDataWFrom[0].Value = kTestWrintingValue;
//
//    auto* chunkTo = new PNC::Chunk(&fix.Data->StructureW, kSize_NodeCapacity, kSize_NodeCount);
//    TEST_VALID_CHUNK_STRUCTDATA(*chunkTo, kSize_NodeCount, kSize_NodeCapacity);
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
//    TEST_VALID_CHUNK_STRUCTDATA(*chunkTo, kSize_NodeCount, kSize_NodeCapacity);
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