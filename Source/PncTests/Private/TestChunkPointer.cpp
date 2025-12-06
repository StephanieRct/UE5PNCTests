
#include "common.h"
#include "TestFixture.h"



// TODO ChunkPointer.Construct VoidData

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_ChunkPointer_Construct_VoidNull, "Pnc.1-ChunkPointer.0-Construct-VoidNull", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_ChunkPointer_Construct_VoidNull::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);
    auto* chunk = new Ni::Containers::NChunkPointer();
    UTEST_TRUE(TEXT("Chunk is Void"), chunk->IsVoid());
    UTEST_TRUE(TEXT("Chunk is Null"), chunk->IsNull());
    UTEST_FALSE(TEXT("Chunk is Struct"), chunk->IsStruct());
    UTEST_FALSE(TEXT("Chunk is Data"), chunk->IsData());
    UTEST_TRUE(TEXT("Chunk is VoidNull"), chunk->IsVoidNull());
    UTEST_FALSE(TEXT("Chunk is VoidData"), chunk->IsVoidData());
    UTEST_FALSE(TEXT("Chunk is StructNull"), chunk->IsStructNull());
    UTEST_FALSE(TEXT("Chunk is StructData"), chunk->IsStructData());
    delete chunk;
    FIXEND;
}
IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_ChunkPointer_Construct_StructNull, "Pnc.1-ChunkPointer.0-Construct-StructNull", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestPnc_ChunkPointer_Construct_StructNull::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);
    auto* chunk = new Ni::Containers::NChunkPointer(&fix.Data->StructureABVW);
    UTEST_FALSE(TEXT("Chunk is Void"), chunk->IsVoid());
    UTEST_TRUE(TEXT("Chunk is Null"), chunk->IsNull());
    UTEST_TRUE(TEXT("Chunk is Struct"), chunk->IsStruct());
    UTEST_FALSE(TEXT("Chunk is Data"), chunk->IsData());
    UTEST_FALSE(TEXT("Chunk is VoidNull"), chunk->IsVoidNull());
    UTEST_FALSE(TEXT("Chunk is VoidData"), chunk->IsVoidData());
    UTEST_TRUE(TEXT("Chunk is StructNull"), chunk->IsStructNull());
    UTEST_FALSE(TEXT("Chunk is StructData"), chunk->IsStructData());
    delete chunk;
    FIXEND;
}
