#ifndef SRC_BENCHMARKS_BENCHMARKS_BASIC_HPP
#define SRC_BENCHMARKS_BENCHMARKS_BASIC_HPP


#include <benchmarks/BenchmarksBase.hpp>


namespace benchmarks
{

	template < typename Desc_ >
	class BasicBenchmarks : public BenchmarksBase<Desc_, typename Desc_::BenchmarksPtr>
	{
		using Base = BenchmarksBase<Desc_, typename Desc_::BenchmarksPtr>;
		using Base::AddSimpleBenchmark;
		using BenchmarkCtx = typename Desc_::BenchmarkCtx;

	public:
		BasicBenchmarks()
			: Base("basic", [](const BenchmarkCtx& ctx) { return ctx.CreateBenchmarks(); })
		{
			using i64 = int64_t;
			using C = typename Desc_::BenchmarkCtx;
			using B = typename Desc_::BenchmarksPtr;

			AddSimpleBenchmark("invokeNative_void_void", [](C& ctx, i64 n, B b){ b->MeasureNativeVoidToVoid(n); });
			AddSimpleBenchmark("invokeNative_void_i32", [](C& ctx, i64 n, B b){ b->MeasureNativeI32ToVoid(n); });
			AddSimpleBenchmark("invokeNative_i32_void", [](C& ctx, i64 n, B b){ b->MeasureNativeVoidToI32(n); });
			AddSimpleBenchmark("invokeNative_void_string3", [](C& ctx, i64 n, B b){ b->MeasureNativeString3ToVoid(n); });
			AddSimpleBenchmark("invokeNative_string3_void", [](C& ctx, i64 n, B b){ b->MeasureNativeVoidToString3(n); });
			AddSimpleBenchmark("invokeNative_void_string100", [](C& ctx, i64 n, B b){ b->MeasureNativeString100ToVoid(n); });
			AddSimpleBenchmark("invokeNative_string100_void", [](C& ctx, i64 n, B b){ b->MeasureNativeVoidToString100(n); });

			AddSimpleBenchmark("invoke_void_void", [](C& ctx, i64 n, B b){ for (int64_t i = 0; i < n; ++i) b->VoidToVoid(); });

			AddSimpleBenchmark("invoke_void_i32", [](C& ctx, i64 n, B b){ for (int64_t i = 0; i < n; ++i) b->I32ToVoid(0); });
			AddSimpleBenchmark("invoke_i32_void", [](C& ctx, i64 n, B b){ for (int64_t i = 0; i < n; ++i) b->VoidToI32(); });

			std::string string3("abc");
			AddSimpleBenchmark("invoke_void_string3", [=](C& ctx, i64 n, B b){ for (int64_t i = 0; i < n; ++i) b->StringToVoid(string3); });
			AddSimpleBenchmark("invoke_string3_void", [=](C& ctx, i64 n, B b){ for (int64_t i = 0; i < n; ++i) b->VoidToString3(); });

			std::string string100("1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");
			AddSimpleBenchmark("invoke_void_string100", [=](C& ctx, i64 n, B b){ for (int64_t i = 0; i < n; ++i) b->StringToVoid(string100); });
			AddSimpleBenchmark("invoke_string100_void", [=](C& ctx, i64 n, B b){ for (int64_t i = 0; i < n; ++i) b->VoidToString100(); });

			AddSimpleBenchmark("invokeOutgoing_void_void", [](C& ctx, i64 n, B b){ b->MeasureOutgoingVoidToVoid(ctx.CreateLocalInvokable(), n); });

			AddSimpleBenchmark("invokeOutgoing_void_i32", [](C& ctx, i64 n, B b){ b->MeasureOutgoingI32ToVoid(ctx.CreateLocalInvokable(), n); });
			AddSimpleBenchmark("invokeOutgoing_i32_void", [](C& ctx, i64 n, B b){ b->MeasureOutgoingVoidToI32(ctx.CreateLocalInvokable(), n); });

			AddSimpleBenchmark("invokeOutgoing_void_string3", [](C& ctx, i64 n, B b){ b->MeasureOutgoingString3ToVoid(ctx.CreateLocalInvokable(), n); });
			AddSimpleBenchmark("invokeOutgoing_string3_void", [](C& ctx, i64 n, B b){ b->MeasureOutgoingVoidToString3(ctx.CreateLocalInvokable(), n); });

			AddSimpleBenchmark("invokeOutgoing_void_string100", [](C& ctx, i64 n, B b){ b->MeasureOutgoingString100ToVoid(ctx.CreateLocalInvokable(), n); });
			AddSimpleBenchmark("invokeOutgoing_string100_void", [](C& ctx, i64 n, B b){ b->MeasureOutgoingVoidToString100(ctx.CreateLocalInvokable(), n); });
		}
	};

}

#endif
