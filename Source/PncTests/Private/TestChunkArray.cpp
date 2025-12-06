#include "common.h"
#include "TestFixture.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_ChunkArray_Construct_StructData, "Pnc.3-ChunkArray.0-Construct-StructData", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_ChunkArray_Construct_StructData::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);
    ResetCallCounter();
    //auto* chunkArray = new Ni::Containers::NArray(&fix.Data->StructureABVW, kSize_ChunkCapacity, kSize_ChunkCount, kSize_NodeCapacity, kSize_NodeCount);
    auto* chunkArray = new Ni::Containers::NArray(&fix.Data->StructureABVW, kSize_ChunkCount, kSize_NodeCountPerChunk);

    auto& internalChunkArray = Ni::Containers::NArrayPointer::GetInternalChunk(*chunkArray);
    TEST_VALID_CHUNKARRAY_STRUCTDATA(*chunkArray, kSize_ChunkCount, kSize_ChunkCount * kSize_NodeCountPerChunk);
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),        CallCounter::Instance.B.Ctor,       kSize_ChunkCount * kSize_NodeCount);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),         CallCounter::Instance.B.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),   CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),   CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),    CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),    CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),       CallCounter::Instance.W.Ctor,       kSize_ChunkCount);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),        CallCounter::Instance.W.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),  CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),  CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),   CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),   CallCounter::Instance.W.MoveAssign, kSize_0);

    ResetCallCounter();
    delete chunkArray;
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),        CallCounter::Instance.B.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),         CallCounter::Instance.B.Dtor,       kSize_ChunkCount * kSize_NodeCount);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),   CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),   CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),    CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),    CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),       CallCounter::Instance.W.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),        CallCounter::Instance.W.Dtor,       kSize_ChunkCount);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),  CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),  CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),   CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),   CallCounter::Instance.W.MoveAssign, kSize_0);
    FIXEND;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_ChunkArray_Construct_StructData_EmptyChunks, "Pnc.3-ChunkArray.0-Construct-StructData-EmptyChunks", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_ChunkArray_Construct_StructData_EmptyChunks::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);
    ResetCallCounter();
    auto* chunkArray = new Ni::Containers::NArray(&fix.Data->StructureABVW, kSize_ChunkCount, kSize_NodeCountPerChunk_0, kSize_ChunkCount * kSize_NodeCountPerChunk);

    auto& internalChunkArray = Ni::Containers::NArrayPointer::GetInternalChunk(*chunkArray);
    TEST_VALID_CHUNKARRAY_STRUCTDATA(*chunkArray, kSize_ChunkCount, kSize_NodeCount_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),        CallCounter::Instance.B.Ctor,       kSize_ChunkCount * kSize_NodeCount_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),         CallCounter::Instance.B.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),   CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),   CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),    CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),    CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),       CallCounter::Instance.W.Ctor,       kSize_ChunkCount);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),        CallCounter::Instance.W.Dtor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),  CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),  CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),   CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),   CallCounter::Instance.W.MoveAssign, kSize_0);

    ResetCallCounter();
    delete chunkArray;
    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),        CallCounter::Instance.B.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),         CallCounter::Instance.B.Dtor,       kSize_ChunkCount * kSize_NodeCount_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),   CallCounter::Instance.B.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),   CallCounter::Instance.B.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),    CallCounter::Instance.B.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),    CallCounter::Instance.B.MoveAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),       CallCounter::Instance.W.Ctor,       kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),        CallCounter::Instance.W.Dtor,       kSize_ChunkCount);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),  CallCounter::Instance.W.CopyCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),  CallCounter::Instance.W.MoveCtor,   kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),   CallCounter::Instance.W.CopyAssign, kSize_0);
    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),   CallCounter::Instance.W.MoveAssign, kSize_0);
    FIXEND;
}
//
//IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_ChunkArray_Construct_StructData_EmptyArray, "Pnc.3-NArray.0-Construct-StructData-EmptyArray", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
//bool TestPnc_ChunkArray_Construct_StructData_EmptyArray::RunTest(const FString& Parameters)
//{
//    FIXSTART(Fix);
//    ResetCallCounter();
//    auto* chunkArray = new Ni::Containers::NArray(&fix.Data->StructureABVW, kSize_ChunkCapacity, kSize_ChunkCount_0, kSize_NodeCapacity, kSize_NodeCount);
//
//    auto& internalChunkArray = Ni::Containers::NArrayPointer::GetInternalChunk(*chunkArray);
//    TEST_VALID_CHUNKARRAY_STRUCTDATA(*chunkArray, kSize_NodeCapacity * kSize_ChunkCapacity, kSize_ChunkCapacity, kSize_ChunkCount_0);
//    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),        CallCounter::Instance.B.Ctor,       kSize_ChunkCount_0 * kSize_NodeCount);
//    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),         CallCounter::Instance.B.Dtor,       kSize_0);
//    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),   CallCounter::Instance.B.CopyCtor,   kSize_0);
//    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),   CallCounter::Instance.B.MoveCtor,   kSize_0);
//    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),    CallCounter::Instance.B.CopyAssign, kSize_0);
//    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),    CallCounter::Instance.B.MoveAssign, kSize_0);
//    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),       CallCounter::Instance.W.Ctor,       kSize_ChunkCount_0);
//    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),        CallCounter::Instance.W.Dtor,       kSize_0);
//    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),  CallCounter::Instance.W.CopyCtor,   kSize_0);
//    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),  CallCounter::Instance.W.MoveCtor,   kSize_0);
//    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),   CallCounter::Instance.W.CopyAssign, kSize_0);
//    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),   CallCounter::Instance.W.MoveAssign, kSize_0);
//
//    ResetCallCounter();
//    delete chunkArray;
//    UTEST_EQUAL(TEXT("Calls to NodeComponent constructor"),        CallCounter::Instance.B.Ctor,       kSize_0);
//    UTEST_EQUAL(TEXT("Calls to NodeComponent destructor"),         CallCounter::Instance.B.Dtor,       kSize_ChunkCount_0 * kSize_NodeCount);
//    UTEST_EQUAL(TEXT("Calls to NodeComponent copy constructor"),   CallCounter::Instance.B.CopyCtor,   kSize_0);
//    UTEST_EQUAL(TEXT("Calls to NodeComponent move constructor"),   CallCounter::Instance.B.MoveCtor,   kSize_0);
//    UTEST_EQUAL(TEXT("Calls to NodeComponent copy assignment"),    CallCounter::Instance.B.CopyAssign, kSize_0);
//    UTEST_EQUAL(TEXT("Calls to NodeComponent move assignment"),    CallCounter::Instance.B.MoveAssign, kSize_0);
//    UTEST_EQUAL(TEXT("Calls to ChunkComponent constructor"),       CallCounter::Instance.W.Ctor,       kSize_0);
//    UTEST_EQUAL(TEXT("Calls to ChunkComponent destructor"),        CallCounter::Instance.W.Dtor,       kSize_ChunkCount_0);
//    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy constructor"),  CallCounter::Instance.W.CopyCtor,   kSize_0);
//    UTEST_EQUAL(TEXT("Calls to ChunkComponent move constructor"),  CallCounter::Instance.W.MoveCtor,   kSize_0);
//    UTEST_EQUAL(TEXT("Calls to ChunkComponent copy assignment"),   CallCounter::Instance.W.CopyAssign, kSize_0);
//    UTEST_EQUAL(TEXT("Calls to ChunkComponent move assignment"),   CallCounter::Instance.W.MoveAssign, kSize_0);
//    FIXEND;
//}