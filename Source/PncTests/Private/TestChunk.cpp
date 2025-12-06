// Fill out your copyright notice in the Description page of Project Settings.


#include "common.h"
#include "TestFixture.h"




IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Chunk_Construct_StructData, "Pnc.2-Chunk.0-Construct-StructData", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Chunk_Construct_StructData::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);
    ResetCallCounter();
    auto* chunk = new Ni::Containers::NChunk(&fix.Data->StructureABVW, kSize_NodeCount);
    TEST_VALID_CHUNKPOINTER_STRUCTDATA_N(*chunk, kSize_NodeCount);
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
    auto* chunkFrom = new Ni::Containers::NChunk(&fix.Data->StructureABVW, kSize_NodeCount);
    TEST_VALID_CHUNKPOINTER_STRUCTDATA_N(*chunkFrom, kSize_NodeCount);

    // Set data to copy from with a known value to test the copy.
    WRITE_COMPONENT(*chunkFrom, Fix::NA, kSize_NodeCount, kTestWrintingValue);
    WRITE_COMPONENT(*chunkFrom, Fix::NB, kSize_NodeCount, kTestWrintingValue);
    WRITE_COMPONENT(*chunkFrom, Fix::CV, kSize_1,         kTestWrintingValue);
    WRITE_COMPONENT(*chunkFrom, Fix::CW, kSize_1,         kTestWrintingValue);
    
    ResetCallCounter();
    auto allocationCountBefore = pnc_allocation_count;
    auto* chunkTo = new Ni::Containers::NChunk(std::move(*chunkFrom));
    
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
    TEST_VALID_CHUNKPOINTER_STRUCTDATA_N(*chunkTo, kSize_NodeCount);
    TEST_VALID_CHUNKPOINTER_VOIDNULL(*chunkFrom);

    TEST_COMPONENT_VALUE("Move Construction TrivialNodeComponent",      *chunkTo, Fix::NA, kSize_NodeCount, kTestWrintingValue);
    TEST_COMPONENT_VALUE("Move Construction NonTrivialNodeComponent",   *chunkTo, Fix::NB, kSize_NodeCount, kTestWrintingValue);
    TEST_COMPONENT_VALUE("Move Construction TrivialChunkComponent",     *chunkTo, Fix::CV, kSize_1,         kTestWrintingValue);
    TEST_COMPONENT_VALUE("Move Construction NonTrivialChunkComponent",  *chunkTo, Fix::CW, kSize_1,         kTestWrintingValue);

    delete chunkTo;
    delete chunkFrom;

    FIXEND;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Chunk_MoveAssignment_Self, "Pnc.2-Chunk.2-MoveAssignment-Self", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Chunk_MoveAssignment_Self::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);

    auto* chunkFromAndTo = new Ni::Containers::NChunk(&fix.Data->StructureABVW, kSize_NodeCount);
    TEST_VALID_CHUNKPOINTER_STRUCTDATA_N(*chunkFromAndTo, kSize_NodeCount);

    auto allocationCountBefore = pnc_allocation_count;
    ResetCallCounter();
    *chunkFromAndTo = std::move(*chunkFromAndTo);
    UTEST_EQUAL(TEXT("Allocation count"), pnc_allocation_count - allocationCountBefore, 0);
    TEST_VALID_CHUNKPOINTER_STRUCTDATA_N(*chunkFromAndTo, kSize_NodeCount);
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
    auto* chunkFrom = new Ni::Containers::NChunk(&fix.Data->StructureABVW, kSize_NodeCount);
    TEST_VALID_CHUNKPOINTER_STRUCTDATA_N(*chunkFrom, kSize_NodeCount);

    // Set data to copy from with a known value to test the copy.
    WRITE_COMPONENT(*chunkFrom, Fix::NA, kSize_NodeCount, kTestWrintingValue);
    WRITE_COMPONENT(*chunkFrom, Fix::NB, kSize_NodeCount, kTestWrintingValue);
    WRITE_COMPONENT(*chunkFrom, Fix::CV, kSize_1,         kTestWrintingValue);
    WRITE_COMPONENT(*chunkFrom, Fix::CW, kSize_1,         kTestWrintingValue);

    auto* chunkTo = new Ni::Containers::NChunk();
    TEST_VALID_CHUNKPOINTER_VOIDNULL(*chunkTo);

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
    TEST_VALID_CHUNKPOINTER_STRUCTDATA_N(*chunkTo, kSize_NodeCount);
    TEST_VALID_CHUNKPOINTER_VOIDNULL(*chunkFrom);

    TEST_COMPONENT_VALUE("Move Construction TrivialNodeComponent",      *chunkTo, Fix::NA, kSize_NodeCount, kTestWrintingValue);
    TEST_COMPONENT_VALUE("Move Construction NonTrivialNodeComponent",   *chunkTo, Fix::NB, kSize_NodeCount, kTestWrintingValue);
    TEST_COMPONENT_VALUE("Move Construction TrivialChunkComponent",     *chunkTo, Fix::CV, kSize_1,         kTestWrintingValue);
    TEST_COMPONENT_VALUE("Move Construction NonTrivialChunkComponent",  *chunkTo, Fix::CW, kSize_1,         kTestWrintingValue);

    delete chunkTo;
    delete chunkFrom;

    FIXEND;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Chunk_MoveAssignment_StructData_VoidNull, "Pnc.2-Chunk.2-MoveAssignment-StructData-VoidNull", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Chunk_MoveAssignment_StructData_VoidNull::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);

    auto* chunkFrom = new Ni::Containers::NChunk();
    TEST_VALID_CHUNKPOINTER_VOIDNULL(*chunkFrom);

    auto allocationCountBefore = pnc_allocation_count;
    auto* chunkTo = new Ni::Containers::NChunk(&fix.Data->StructureABVW, kSize_NodeCount);
    TEST_VALID_CHUNKPOINTER_STRUCTDATA_N(*chunkTo, kSize_NodeCount);

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
    TEST_VALID_CHUNKPOINTER_VOIDNULL(*chunkTo);
    TEST_VALID_CHUNKPOINTER_VOIDNULL(*chunkFrom);

    delete chunkTo;
    delete chunkFrom;

    FIXEND;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Chunk_MoveAssignment_StructData_StructData_SameStruct, "Pnc.2-Chunk.2-MoveAssignment-StructData-StructData-SameStruct", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Chunk_MoveAssignment_StructData_StructData_SameStruct::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);

    auto* chunkFrom = new Ni::Containers::NChunk(&fix.Data->StructureABVW, kSize_NodeCount);
    TEST_VALID_CHUNKPOINTER_STRUCTDATA_N(*chunkFrom, kSize_NodeCount);
    WRITE_COMPONENT(*chunkFrom, Fix::NA, kSize_NodeCount, kTestWrintingValue);
    WRITE_COMPONENT(*chunkFrom, Fix::NB, kSize_NodeCount, kTestWrintingValue);
    WRITE_COMPONENT(*chunkFrom, Fix::CV, kSize_1,         kTestWrintingValue);
    WRITE_COMPONENT(*chunkFrom, Fix::CW, kSize_1,         kTestWrintingValue);

    auto allocationCountBefore = pnc_allocation_count;
    auto* chunkTo = new Ni::Containers::NChunk(&fix.Data->StructureABVW, kSize_NodeCountLow);
    TEST_VALID_CHUNKPOINTER_STRUCTDATA_N(*chunkTo, kSize_NodeCountLow);

    ResetCallCounter();
    *chunkTo = std::move(*chunkFrom);
    UTEST_EQUAL(TEXT("Allocation count"), pnc_allocation_count - allocationCountBefore, 0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),        CallCounter::Instance.B.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),         CallCounter::Instance.B.Dtor,       kSize_NodeCountLow);
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
    TEST_VALID_CHUNKPOINTER_STRUCTDATA_N(*chunkTo, kSize_NodeCount);
    TEST_VALID_CHUNKPOINTER_VOIDNULL(*chunkFrom);
    
    TEST_COMPONENT_VALUE("Move Construction TrivialNodeComponent",      *chunkTo, Fix::NA, kSize_NodeCount, kTestWrintingValue);
    TEST_COMPONENT_VALUE("Move Construction NonTrivialNodeComponent",   *chunkTo, Fix::NB, kSize_NodeCount, kTestWrintingValue);
    TEST_COMPONENT_VALUE("Move Construction TrivialChunkComponent",     *chunkTo, Fix::CV, kSize_1,         kTestWrintingValue);
    TEST_COMPONENT_VALUE("Move Construction NonTrivialChunkComponent",  *chunkTo, Fix::CW, kSize_1,         kTestWrintingValue);
    delete chunkTo;
    delete chunkFrom;

    FIXEND;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Chunk_MoveAssignment_StructData_StructData_DiffStruct, "Pnc.2-Chunk.2-MoveAssignment-StructData-StructData-DiffStruct", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Chunk_MoveAssignment_StructData_StructData_DiffStruct::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);

    auto* chunkFrom = new Ni::Containers::NChunk(&fix.Data->StructureABVW, kSize_NodeCount);
    TEST_VALID_CHUNKPOINTER_STRUCTDATA_N(*chunkFrom, kSize_NodeCount);

    auto allocationCountBefore = pnc_allocation_count;
    auto* chunkTo = new Ni::Containers::NChunk(&fix.Data->StructureBW, kSize_NodeCountLow);
    TEST_VALID_CHUNKPOINTER_STRUCTDATA_N(*chunkTo, kSize_NodeCountLow);

    ResetCallCounter();
    *chunkTo = std::move(*chunkFrom);
    UTEST_EQUAL(TEXT("Allocation count"), pnc_allocation_count - allocationCountBefore, 0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),        CallCounter::Instance.B.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),         CallCounter::Instance.B.Dtor,       kSize_NodeCountLow);
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
    TEST_VALID_CHUNKPOINTER_STRUCTDATA_N(*chunkTo, kSize_NodeCount);
    TEST_VALID_CHUNKPOINTER_VOIDNULL(*chunkFrom);

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
    auto* chunkFrom = new Ni::Containers::NChunk();
    TEST_VALID_CHUNKPOINTER_VOIDNULL(*chunkFrom);

    ResetCallCounter();
    auto* chunkTo = new Ni::Containers::NChunk(*chunkFrom);
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
    TEST_VALID_CHUNKPOINTER_VOIDNULL(*chunkTo);

    delete chunkTo;
    delete chunkFrom;

    FIXEND;
}
IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Chunk_CopyConstruction_StructData, "Pnc.2-Chunk.3-CopyConstruction-StructData", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Chunk_CopyConstruction_StructData::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);
    auto* chunkFrom = new Ni::Containers::NChunk(&fix.Data->StructureABVW, kSize_NodeCount);
    TEST_VALID_CHUNKPOINTER_STRUCTDATA_N(*chunkFrom, kSize_NodeCount);

    // Set data to copy from with a known value to test the copy.
    WRITE_COMPONENT(*chunkFrom, Fix::NA, kSize_NodeCount, kTestWrintingValue);
    WRITE_COMPONENT(*chunkFrom, Fix::NB, kSize_NodeCount, kTestWrintingValue);
    WRITE_COMPONENT(*chunkFrom, Fix::CV, kSize_1,         kTestWrintingValue);
    WRITE_COMPONENT(*chunkFrom, Fix::CW, kSize_1,         kTestWrintingValue);

    ResetCallCounter();
    auto* chunkTo = new Ni::Containers::NChunk(*chunkFrom);
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
    TEST_VALID_CHUNKPOINTER_STRUCTDATA_N(*chunkTo, kSize_NodeCount);

    TEST_COMPONENT_VALUE("Copy Construction TrivialNodeComponent",      *chunkTo, Fix::NA, kSize_NodeCount, kTestWrintingValue);
    TEST_COMPONENT_VALUE("Copy Construction NonTrivialNodeComponent",   *chunkTo, Fix::NB, kSize_NodeCount, kTestWrintingValue);
    TEST_COMPONENT_VALUE("Copy Construction TrivialChunkComponent",     *chunkTo, Fix::CV, kSize_1,         kTestWrintingValue);
    TEST_COMPONENT_VALUE("Copy Construction NonTrivialChunkComponent",  *chunkTo, Fix::CW, kSize_1,         kTestWrintingValue);

    delete chunkTo;
    delete chunkFrom;

    FIXEND;
}



// Copy to chunk with enough space
// Copy to chunk without enough space

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Chunk_CopyAssignment_Self, "Pnc.2-Chunk.4-CopyAssignment-Self", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Chunk_CopyAssignment_Self::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);

    auto* chunkFromAndTo = new Ni::Containers::NChunk(&fix.Data->StructureABVW, kSize_NodeCount);
    TEST_VALID_CHUNKPOINTER_STRUCTDATA_N(*chunkFromAndTo, kSize_NodeCount);

    auto allocationCountBefore = pnc_allocation_count;
    ResetCallCounter();
    *chunkFromAndTo = *chunkFromAndTo;
    UTEST_EQUAL(TEXT("Allocation count"), pnc_allocation_count - allocationCountBefore, 0);
    TEST_VALID_CHUNKPOINTER_STRUCTDATA_N(*chunkFromAndTo, kSize_NodeCount);
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
    auto* chunkFrom = new Ni::Containers::NChunk(&fix.Data->StructureABVW, kSize_NodeCount);
    TEST_VALID_CHUNKPOINTER_STRUCTDATA_N(*chunkFrom, kSize_NodeCount);

    // Set data to copy from with a known value to test the copy.
    WRITE_COMPONENT(*chunkFrom, Fix::NA, kSize_NodeCount, kTestWrintingValue);
    WRITE_COMPONENT(*chunkFrom, Fix::NB, kSize_NodeCount, kTestWrintingValue);
    WRITE_COMPONENT(*chunkFrom, Fix::CV, kSize_1,         kTestWrintingValue);
    WRITE_COMPONENT(*chunkFrom, Fix::CW, kSize_1,         kTestWrintingValue);

    auto* chunkTo = new Ni::Containers::NChunk();
    TEST_VALID_CHUNKPOINTER_VOIDNULL(*chunkTo);

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
    TEST_VALID_CHUNKPOINTER_STRUCTDATA_N(*chunkTo, kSize_NodeCount);
    UTEST_TRUE(TEXT("ChunkTo is not the same data as ChunkFrom"), !Ni::Containers::NChunkPointer::IsSameData(*chunkTo, *chunkFrom));

    TEST_COMPONENT_VALUE("Copy Assignment TrivialNodeComponent",      *chunkTo, Fix::NA, kSize_NodeCount, kTestWrintingValue);
    TEST_COMPONENT_VALUE("Copy Assignment NonTrivialNodeComponent",   *chunkTo, Fix::NB, kSize_NodeCount, kTestWrintingValue);
    TEST_COMPONENT_VALUE("Copy Assignment TrivialChunkComponent",     *chunkTo, Fix::CV, kSize_1,         kTestWrintingValue);
    TEST_COMPONENT_VALUE("Copy Assignment NonTrivialChunkComponent",  *chunkTo, Fix::CW, kSize_1,         kTestWrintingValue);

    delete chunkTo;
    delete chunkFrom;

    FIXEND;
}
IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Chunk_CopyAssignment_StructData_VoidNull, "Pnc.2-Chunk.4-CopyAssignment-StructData-VoidNull", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Chunk_CopyAssignment_StructData_VoidNull::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);
    auto* chunkFrom = new Ni::Containers::NChunk();
    TEST_VALID_CHUNKPOINTER_VOIDNULL(*chunkFrom);

    auto allocationCountBefore = pnc_allocation_count;
    auto* chunkTo = new Ni::Containers::NChunk(&fix.Data->StructureABVW, kSize_NodeCount);
    TEST_VALID_CHUNKPOINTER_STRUCTDATA_N(*chunkTo, kSize_NodeCount);

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
    TEST_VALID_CHUNKPOINTER_VOIDNULL(*chunkTo);

    delete chunkTo;
    delete chunkFrom;

    FIXEND;
}
IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Chunk_CopyAssignment_StructData_StructData_SameStruct, "Pnc.2-Chunk.4-CopyAssignment-StructData-StructData-SameStruct", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Chunk_CopyAssignment_StructData_StructData_SameStruct::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);

    auto* chunkFrom = new Ni::Containers::NChunk(&fix.Data->StructureABVW, kSize_NodeCount);
    TEST_VALID_CHUNKPOINTER_STRUCTDATA_N(*chunkFrom, kSize_NodeCount);

    auto allocationCountBefore = pnc_allocation_count;
    auto* chunkTo = new Ni::Containers::NChunk(&fix.Data->StructureABVW, kSize_NodeCountLow);
    TEST_VALID_CHUNKPOINTER_STRUCTDATA_N(*chunkTo, kSize_NodeCountLow);

    ResetCallCounter();
    *chunkTo = *chunkFrom;
    UTEST_GREATER(TEXT("Allocation count"), pnc_allocation_count - allocationCountBefore, 0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),        CallCounter::Instance.B.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),         CallCounter::Instance.B.Dtor,       kSize_NodeCountLow);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),   CallCounter::Instance.B.CopyCtor,   kSize_NodeCount);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),   CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),    CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),    CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),       CallCounter::Instance.W.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),        CallCounter::Instance.W.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),  CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),  CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),   CallCounter::Instance.W.CopyAssign, kSize_1);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),   CallCounter::Instance.W.MoveAssign, kSize_0);
    TEST_VALID_CHUNKPOINTER_STRUCTDATA_N(*chunkTo, kSize_NodeCount);
    TEST_VALID_CHUNKPOINTER_STRUCTDATA_N(*chunkFrom, kSize_NodeCount);

    delete chunkTo;
    delete chunkFrom;

    FIXEND;
}
IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Chunk_CopyAssignment_StructData_StructData_DiffStruct, "Pnc.2-Chunk.4-CopyAssignment-StructData-StructData-DiffStruct", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Chunk_CopyAssignment_StructData_StructData_DiffStruct::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);

    auto* chunkFrom = new Ni::Containers::NChunk(&fix.Data->StructureABVW, kSize_NodeCount);
    TEST_VALID_CHUNKPOINTER_STRUCTDATA_N(*chunkFrom, kSize_NodeCount);

    auto allocationCountBefore = pnc_allocation_count;
    auto* chunkTo = new Ni::Containers::NChunk(&fix.Data->StructureBW, kSize_NodeCountLow);
    TEST_VALID_CHUNKPOINTER_STRUCTDATA_N(*chunkTo, kSize_NodeCountLow);

    ResetCallCounter();
    *chunkTo = *chunkFrom;
    UTEST_GREATER(TEXT("Allocation count"), pnc_allocation_count - allocationCountBefore, 0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),        CallCounter::Instance.B.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),         CallCounter::Instance.B.Dtor,       kSize_NodeCountLow);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),   CallCounter::Instance.B.CopyCtor,   kSize_NodeCount);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),   CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),    CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),    CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),       CallCounter::Instance.W.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),        CallCounter::Instance.W.Dtor,       kSize_1);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),  CallCounter::Instance.W.CopyCtor,   kSize_1);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),  CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),   CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),   CallCounter::Instance.W.MoveAssign, kSize_0);
    TEST_VALID_CHUNKPOINTER_STRUCTDATA_N(*chunkTo, kSize_NodeCount);
    TEST_VALID_CHUNKPOINTER_STRUCTDATA_N(*chunkFrom, kSize_NodeCount);

    delete chunkTo;
    delete chunkFrom;

    FIXEND;
}

struct TestAlgoSetComponentA : public Ni::Containers::Algorithm<TestAlgoSetComponentA>
{
public:
    TestNodeComponentA* Component;
    int Value;

    TestAlgoSetComponentA(int value)
        : Component(nullptr)
        , Value(value)
    {
    }

    template<typename T>
    bool Requirements(T req)
    {
        if (!req.Component(Component)) return false;
        return true;
    }

    void Execute(int count)const
    {
        for (int i = 0; i < count; ++i)
        {
            Component[i].Value = Value;
        }
    }
};
IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Chunk_Algo, "Pnc.2-Chunk.5-Algo", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_Chunk_Algo::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);

    Ni::Containers::NChunk chunk(&fix.Data->StructureABVW, kSize_NodeCount);
    TEST_VALID_CHUNKPOINTER_STRUCTDATA_N(chunk, kSize_NodeCount);
    TestAlgoSetComponentA algoTestAlgoSetComponentA(kTestWrintingValue);
    algoTestAlgoSetComponentA.Run(&chunk);
    TEST_COMPONENT_VALUE("algoTestAlgoSetComponentA.Run", chunk, Fix::NA, kSize_NodeCount, kTestWrintingValue);
    FIXEND;
}


