#include "TestFixture.h"
#include <random>
#include <numeric>

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
template<typename T>
struct MoveablePtr
{
    T* Ptr;
    MoveablePtr(T* ptr)
        :Ptr(ptr) 
    {
    }
    MoveablePtr(MoveablePtr&& other)
        :Ptr(other.Ptr)
    {
        other.Ptr = nullptr;
    }
    MoveablePtr& operator=(MoveablePtr&& other)
    {
        auto ptr = other.Ptr;
        other.Ptr = nullptr;
        Ptr = ptr;
        return *this;
    }
    bool IsValid() const { return Ptr != nullptr; }
};
struct StrideBuffer
{
    std::size_t CacheLineSize;
    std::size_t StrideCacheLine; // best if aligned with cache associativeness
    std::size_t StrideCount; // best if aligned with cache associativeness
    MoveablePtr<uint8> Buffer;
    bool OwnBuffer;
    double Average;
    double StdDeviation;
    double Min;
    double Max;
    std::vector<double> IterationTimes;

    double ValidTotalTime;
    size_t ValidIterationCount;

    std::size_t ResultWarmup;
    std::size_t Result;
    StrideBuffer(const std::size_t cacheLineSize, const std::size_t strideCacheLines, const std::size_t strideCount, const std::size_t iterationCount)
        : CacheLineSize(cacheLineSize)
        , StrideCacheLine(strideCacheLines)
        , StrideCount(strideCount)
        , Buffer(nullptr)
        , OwnBuffer(false)
        , Average(0)
        , StdDeviation(0)
        , IterationTimes(iterationCount)
        , ValidTotalTime(0)
        , ValidIterationCount(0)
        , ResultWarmup(0)
        , Result(0)
    {
    }
    StrideBuffer(const std::size_t cacheLineSize, const std::size_t strideCacheLines, const std::size_t strideCount, const std::size_t iterationCount, uint8* buffer)
        : CacheLineSize(cacheLineSize)
        , StrideCacheLine(strideCacheLines)
        , StrideCount(strideCount)
        , Buffer(buffer)
        , OwnBuffer(false)
        , Average(0)
        , StdDeviation(0)
        , IterationTimes(iterationCount)
        , ValidTotalTime(0)
        , ValidIterationCount(0)
        , ResultWarmup(0)
        , Result(0)
    {
    }
    StrideBuffer(const StrideBuffer&) = delete;
    StrideBuffer& operator=(const StrideBuffer&) = delete;
    StrideBuffer(StrideBuffer&&) = default;
    StrideBuffer& operator=(StrideBuffer&&) = default;
    ~StrideBuffer()
    {
        Free();
    }
    std::size_t GetBufferSize()const { return CacheLineSize * StrideCacheLine * StrideCount; }
    void Allocate()
    {
        Free();
        Buffer = (uint8*)pnc_alloc(GetBufferSize(), CacheLineSize);
        WriteIndex();
        OwnBuffer = true;
    }
    void Free()
    {
        if (Buffer.IsValid() && OwnBuffer)
            pnc_free_dirty(Buffer.Ptr, GetBufferSize(), CacheLineSize);
        Buffer = nullptr;
        OwnBuffer = false;
    }
    void WriteIndex()
    {
        std::size_t cacheLineSize = CacheLineSize;
        std::size_t strideCacheLine = StrideCacheLine;
        std::size_t totalCacheLines = StrideCacheLine * StrideCount;
        std::size_t lastStride = StrideCacheLine * (StrideCount -1);
        for (std::size_t i = 0; i < totalCacheLines - 1; ++i)
            *GetCacheLineAddress(i) = strideCacheLine + i;
        for (std::size_t i = 0; i < strideCacheLine; ++i)
            *GetCacheLineAddress(lastStride + i) = i;
    }
    std::size_t* GetCacheLineAddress(const std::size_t index)
    {
        return (std::size_t*)(Buffer.Ptr + index * CacheLineSize);
    }
    std::size_t ReadLoop(std::size_t count)
    {
        std::size_t cacheLineSize = CacheLineSize;
        std::size_t cacheLineIndex = 0;
        while (count-- > 0)
            cacheLineIndex = *(std::size_t*)(Buffer.Ptr + cacheLineIndex * cacheLineSize);
        return cacheLineIndex;
    }
};
void swap(StrideBuffer& a, StrideBuffer& b)
{
    StrideBuffer tmp = std::move(a);
    a = std::move(b);
    b = std::move(tmp);

}
//EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter
IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPnc_Pnc_Perf_CacheStride, "PncPerf.CacheStride", EAutomationTestFlags::EditorContext | EAutomationTestFlags::PerfFilter)
bool TestPnc_Pnc_Perf_CacheStride::RunTest(const FString& Parameters)
{
    constexpr std::size_t kIterationCount = 128;
    constexpr std::size_t kCacheLineSize = 64;
    constexpr std::size_t kMinStrideCacheLine = 1;
    constexpr std::size_t kMaxStrideCacheLine = 256;
    constexpr std::size_t kMulStrideCacheLine = 1;
    constexpr std::size_t kReadCount = 1024 * 64;
    constexpr std::size_t kStrideCount = 256;//128

    size_t bufferSize = kCacheLineSize * kMaxStrideCacheLine * kMulStrideCacheLine * kStrideCount ;
    UTEST_LESS_EQUAL("buffer size", bufferSize, 1024 * 1024 * 1024);
    uint8* buffer = (uint8*)pnc_alloc(bufferSize, kCacheLineSize);
    std::vector< StrideBuffer> tests;
    for (std::size_t iStride = kMinStrideCacheLine; iStride < kMaxStrideCacheLine+1; ++iStride)
    {
        std::size_t stride = iStride * kMulStrideCacheLine;// pow(2, iStride);
        auto test = StrideBuffer(kCacheLineSize, stride, kStrideCount, kIterationCount, buffer);
        //test.Allocate();
        tests.push_back(std::move(test));
    }

    for (auto& test : tests)
    {
        test.WriteIndex();
        //auto rng = std::default_random_engine{};
        //std::shuffle(tests.begin(), tests.end(), rng);
        for (std::size_t i = 0; i < kIterationCount; ++i)
        {
            //std::atomic_thread_fence(std::memory_order_acq_rel);
            //test.ResultWarmup = test.ReadLoop(kReadCount);
            //std::atomic_thread_fence(std::memory_order_acq_rel);

            double startTime = FPlatformTime::Seconds();
            std::size_t result = test.ReadLoop(kReadCount);
            std::atomic_thread_fence(std::memory_order_acq_rel);
            double endTime = FPlatformTime::Seconds();
            double duration = endTime - startTime;

            test.Average += duration * 1000000 / kIterationCount;
            test.Result = result;
            test.IterationTimes[i] = duration * 1000000;
        }
    }

    for (auto& test : tests)
    {
        double variance = 0;
        test.Min = std::numeric_limits<size_t>::max();
        test.Max = std::numeric_limits<size_t>::min();
        for (std::size_t i = 0; i < kIterationCount; ++i)
        {
            test.Min = std::min(test.Min, test.IterationTimes[i]);
            test.Max = std::max(test.Max, test.IterationTimes[i]);
            auto diff = test.IterationTimes[i] - test.Average;
            variance += diff * diff / kIterationCount;
        }
        test.StdDeviation = sqrt(variance);
    }
    //for (std::size_t i = 0; i < kIterationCount; ++i)
    //{
    //    auto rng = std::default_random_engine{};
    //    std::shuffle(tests.begin(), tests.end(), rng);
    //    for (auto& test : tests)
    //    {
    //        std::atomic_thread_fence(std::memory_order_acq_rel);
    //        double startTime = FPlatformTime::Seconds();
    //        std::size_t result = test.ReadLoop(kReadCount);
    //        std::atomic_thread_fence(std::memory_order_acq_rel);
    //        double endTime = FPlatformTime::Seconds();
    //        double duration = (endTime - startTime) * 1000000;
    //        test.Result = result;
    //        if (abs(duration - test.Average) < test.StdDeviation)
    //        {
    //            test.ValidTotalTime += duration;
    //            ++test.ValidIterationCount;
    //        }
    //    }
    //}

    this->AddInfo(FString::Printf(TEXT("BufferSize: %d\nStride Count: %d\nLineStride\tAvg(us)   \tStdDev(us)\tMin       \tMax       \t   Size(b)\t Stride(b)\tresult "), bufferSize, kStrideCount));
    std::sort(tests.begin(), tests.end(), [](const StrideBuffer& a, const StrideBuffer& b) { return a.StrideCacheLine < b.StrideCacheLine; });
    for (auto& test : tests)
    {
        this->AddInfo(FString::Printf(TEXT("%10d\t%-10.2f\t%-10.2f\t%-10.2f\t%-10.2f\t%10d\t%10d\t%-10d"), test.StrideCacheLine, test.Average, test.StdDeviation, test.Min, test.Max, test.GetBufferSize(), test.StrideCacheLine * kCacheLineSize, test.Result));
        test.Free();
    }
    pnc_free_dirty(buffer, bufferSize, kCacheLineSize);
    return true;
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
    constexpr uint32 kCacheLineSize = 64;
    constexpr uint32 kAlignment = 1024;
    constexpr uint32 kNoiseCount = 16;
    constexpr uint32 kNoiseInBetweenCount = 0;
    constexpr uint32 kStrideCount = 4;
    constexpr uint32 kStrideStep = sizeof(uint32) * 32;
    constexpr uint32 kStrideMax = kStrideCount * kStrideStep;
    constexpr uint32 kReadCount = 1024 * 32;
    constexpr uint32 kIterationCount = 64;
    constexpr bool kReadNoise = true;
    uint32 totalNoiseSize = 0;
    uint32 currentStride = 0;
    uint8* singleBuffer = (uint8*)pnc_alloc(kStrideMax * kReadCount, kAlignment);
    for (uint32 iNoise = 0; iNoise < kNoiseCount; ++iNoise)
    {
        uint32 noiseDataSize32 = 1024 * 32;
        totalNoiseSize += noiseDataSize32;
        uint32* noiseData = (uint32*)pnc_alloc(noiseDataSize32 * sizeof(uint32), kAlignment);
        uint32 checksum = 0;
        for (uint32 k = 0; k < noiseDataSize32; ++k)
            checksum += noiseData[k] = k + 1;
        noises.push_back(TestNoise{ noiseData, noiseDataSize32, checksum });
    }
    for (uint32 i = 0; i < kStrideCount; ++i)
    {
        for (uint32 iNoise = 0; iNoise < kNoiseInBetweenCount; ++iNoise)
        {
            uint32 noiseDataSize32 =  (iNoise * iNoise * iNoise+512) % (1024-1) + 1;
            totalNoiseSize += noiseDataSize32;
            uint32* noiseData = (uint32 *) pnc_alloc(noiseDataSize32 * sizeof(uint32), kAlignment);
            uint32 checksum = 0;
            for (uint32 k = 0; k < noiseDataSize32; ++k)
                checksum += noiseData[k] = k + 1;
            noises.push_back(TestNoise{ noiseData, noiseDataSize32, checksum });
        }
        uint32 stride = std::max((uint32)sizeof(uint32), currentStride);//(sizeof(uint32) + i * kStrideStep);
        currentStride += kStrideStep;

        uint32 dataSize = kReadCount * stride;
        uint8* data = singleBuffer;// (uint8*)pnc_alloc(dataSize, kAlignment);
        memset(data, 0, dataSize);
        tests.push_back(TestStride{ data, dataSize, stride });

        for (uint32 k = 0; k < kReadCount; ++k)
        {
            *(uint32*)(data + k * stride) = k + 1;
        }
    }
    for (uint32 k = 0; k < kStrideMax * kReadCount / sizeof(uint32); ++k)
    {
        ((uint32*)singleBuffer)[k] = 3;
    }
    for (uint32 iter = 0; iter < kIterationCount; ++iter)
    {
        auto rng = std::default_random_engine{};
        std::shuffle(tests.begin(), tests.end(), rng);
        std::shuffle(noises.begin(), noises.end(), rng);
        for (auto& t : tests)
        {
            
            if (kReadNoise)
            {
                for (auto& noise : noises)
                {
                    uint32 checksum = 0;
                    for (uint32 k = 0; k < noise.DataSize32; ++k)
                        checksum += noise.Data[k];
                    UTEST_EQUAL("Checksum", checksum, noise.Checksum);
                }
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

            UTEST_EQUAL("Checksum", sum, kReadCount * 3);
            //UTEST_EQUAL("Checksum", sum, (kReadCount * (kReadCount + 1) / 2)); // infinit series 1 + 2 + 3 + 4 + ... for f(n) = n(n+1)/2
        }

    }

    this->AddInfo(FString::Printf(TEXT("totalNoiseSize %d"), totalNoiseSize));
    this->AddInfo(TEXT("Stride\tAvg us"));
    std::sort(tests.begin(), tests.end(), [](const TestStride& a, const TestStride& b) { return a.Stride < b.Stride; });
    for (auto& t : tests)
    {
        AddTelemetryData(FString::Printf(TEXT("Stride %d Total"), t.Stride), t.TotalTime);
        AddTelemetryData(FString::Printf(TEXT("Stride %d Avg"), t.Stride), t.TotalTime / kIterationCount);
        FString message = FString::Printf(TEXT("%7d\t%f"), t.Stride, t.TotalTime / kIterationCount * 1000000);
        this->AddInfo(message);
        //UE_LOG(LogTemp, Log, TEXT("%s"), *message);

        //pnc_free_dirty(t.Data, t.DataSize, kAlignment);
    }
    for (auto& noise : noises)
    {
        pnc_free_dirty(noise.Data, noise.DataSize32 * sizeof(uint32), alignof(uint32));
    }
    pnc_free_dirty(singleBuffer, kStrideMax* kReadCount, kAlignment);
    
    return true;
}
