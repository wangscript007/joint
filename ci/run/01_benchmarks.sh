[ "$RUN_BENCHMARKS" -ne 0 ] || exit 0

[ "$BENCHMARKS_NUM_PASSES" ] || BENCHMARKS_NUM_PASSES=2

Verbose "$SOURCE_DIR/benchmarks/ci/runner.py" \
	--executable "$MAIN_DIR/build/bin/joint-benchmarks" \
	--reference-executable "$REFERENCE_JOINT_DIR/build/bin/joint-benchmarks" \
	--benchmarks "$SOURCE_DIR/benchmarks/ci/benchmarks.json" \
	--num-passes "$BENCHMARKS_NUM_PASSES" ||
exit 1
