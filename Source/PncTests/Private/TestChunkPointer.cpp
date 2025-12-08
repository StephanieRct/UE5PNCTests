
#include "common.h"
#include "TestFixture.h"



// TODO ChunkPointer.Construct VoidData

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestNi_ChunkPointer_Construct_VoidNull, "Ni.1-ChunkPointer.0-Construct-VoidNull", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestNi_ChunkPointer_Construct_VoidNull::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);
    auto* chunk = new Ni::NChunkPointer();
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
IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestNi_ChunkPointer_Construct_StructNull, "Ni.1-ChunkPointer.0-Construct-StructNull", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool TestNi_ChunkPointer_Construct_StructNull::RunTest(const FString& Parameters)
{
    FIXSTART(Fix);
    auto* chunk = new Ni::NChunkPointer(&fix.Data->StructureABVW);
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
