
#include "TestFixture.h"

CallCounter CallCounter::Instance;

void ResetCallCounter()
{
    CallCounter::Instance.Reset();
}
//
//void TestAssert()
//{
//    pnc_assert(false == true);
//}
//void TestAssertf(int a)
//{
//    pnc_assertf(false == true, TEXT("This is my assertf with argument of value '%d'"), a);
//}
//void TestAssertNoEntry()
//{
//    pnc_assert_no_entry_return();
//}
//
//IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Fixture_Exceptions, "Pnc.0Fixture.Exceptions", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
//bool TestPnc_Fixture_Exceptions::RunTest(const FString& Parameters)
//{
//    try
//    {
//        TestAssert();
//        UTEST_TRUE(TEXT("pnc_assert must throw an execption"), false);
//    }
//    catch (const FString& msg)
//    {
//        UE_LOG(LogTemp, Log, TEXT("Catch execption '%s'"), *msg);
//    }
//    catch(...)
//    {
//        UTEST_TRUE(TEXT("pnc_assert throws unknown execption, should be a FString"), false);
//    }
//
//    try
//    {
//        TestAssertf(5);
//        UTEST_TRUE(TEXT("pnc_assertf must throw an execption"), false);
//    }
//    catch (const FString& msg)
//    {
//        UE_LOG(LogTemp, Log, TEXT("Catch execption '%s'"), *msg);
//    }
//    catch (...)
//    {
//        UTEST_TRUE(TEXT("pnc_assertf throws unknown execption, should be a FString"), false);
//    }
//
//    try
//    {
//        TestAssertNoEntry();
//        UTEST_TRUE(TEXT("pnc_assert_no_entry_return must throw an execption"), false);
//    }
//    catch (const FString& msg)
//    {
//        UE_LOG(LogTemp, Log, TEXT("Catch execption '%s'"), *msg);
//    }
//    catch (...)
//    {
//        UTEST_TRUE(TEXT("pnc_assert_no_entry_return throws unknown execption, should be a FString"), false);
//    }
//
//    return true;
//}

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


//EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter
IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Pnc_Perf_SequentialRead, "PncPerf.SequentialRead", EAutomationTestFlags::EditorContext | EAutomationTestFlags::PerfFilter)
bool TestPnc_Pnc_Perf_SequentialRead::RunTest(const FString& Parameters)
{
    struct TestStride
    {
        uint8* Data;
        uint32 DataSize;
        uint32 Stride;
        double TotalTime;
    };
    std::vector< TestStride> tests;

    struct TestNoise
    {
        uint32* Data;
        uint32 DataSize32;
        uint32 Checksum;
    };
    std::vector<TestNoise> noises;
    constexpr uint32 kNoiseCount = 128;
    constexpr uint32 kStrideCount = 64;
    constexpr uint32 kReadCount = 1024 * 32;
    constexpr uint32 kIterationCount = 256;
    uint32 totalNoiseSize = 0;
    for (uint32 i = 0; i < kStrideCount; ++i)
    {
        for (uint32 iNoise = 0; iNoise < kNoiseCount; ++iNoise)
        {
            uint32 noiseDataSize32 =  (iNoise * iNoise * iNoise) % (1024-1) + 1;
            totalNoiseSize += noiseDataSize32;
            uint32* noiseData = (uint32 *) pnc_alloc(noiseDataSize32 * sizeof(uint32), alignof(uint32));
            uint32 checksum = 0;
            for (uint32 k = 0; k < noiseDataSize32; ++k)
                checksum += noiseData[k] = k + 1;
            noises.push_back(TestNoise{ noiseData, noiseDataSize32, checksum });
        }

        uint32 stride = (sizeof(uint32) + i*4);
        uint32 dataSize = kReadCount * stride;
        uint8* data = (uint8*)pnc_alloc(dataSize, 4);
        memset(data, 0, dataSize);
        tests.push_back(TestStride{ data, dataSize, stride });
        for (uint32 k = 0; k < kReadCount; ++k)
        {
            *(uint32*)(data + k * stride) = k + 1;
        }
    }
    for (uint32 iter = 0; iter < kIterationCount; ++iter)
    {
        for (auto& t : tests)
        {
            
            for (auto& noise : noises)
            {
                uint32 checksum = 0;
                for (uint32 k = 0; k < noise.DataSize32; ++k)
                    checksum += noise.Data[k];
                UTEST_EQUAL("Checksum", checksum, noise.Checksum);
            }

            uint32 sum = 0;
            double startTime = FPlatformTime::Seconds();
            for (uint32 i = 0; i < kReadCount; ++i)
            {
                sum += *(uint32*)(t.Data + i * t.Stride);
            }
            double endTime = FPlatformTime::Seconds();
            double duration = endTime - startTime;
            t.TotalTime += duration;
            UTEST_EQUAL("Checksum", sum, (kReadCount * (kReadCount + 1) / 2)); // infinit series 1 + 2 + 3 + 4 + ... for f(n) = n(n+1)/2
        }
    }

    this->AddInfo(FString::Printf(TEXT("totalNoiseSize %d"), totalNoiseSize));
    this->AddInfo(TEXT("Stride\tAvg us"));
    for (auto& t : tests)
    {
        AddTelemetryData(FString::Printf(TEXT("Stride %d Total"), t.Stride), t.TotalTime);
        AddTelemetryData(FString::Printf(TEXT("Stride %d Avg"), t.Stride), t.TotalTime / kIterationCount);
        FString message = FString::Printf(TEXT("%7d\t%f"), t.Stride, t.TotalTime / kIterationCount * 1000000);
        this->AddInfo(message);
        //UE_LOG(LogTemp, Log, TEXT("%s"), *message);

        pnc_free_dirty(t.Data, t.DataSize, 4);
    }
    for (auto& noise : noises)
    {
        pnc_free_dirty(noise.Data, noise.DataSize32 * sizeof(uint32), alignof(uint32));
    }
    return true;
}
