[ "$TEST_COVERAGE" -ne 0 ] || exit 0

ZeroInit UPLOAD_COVERAGE

echo "Sending coverage info"

ToCoveralls() {
    coveralls-lcov --repo-token ${COVERALLS_TOKEN} coverage.info || ( echo "Coveralls did not collect coverage reports"; return 1 )
}

ToCodecov() {
    bash <(curl -s https://codecov.io/bash) || ( echo "Codecov did not collect coverage reports"; return 1 )
}

Upload() {
    if [ $UPLOAD_COVERAGE -eq 0 ]; then
        Log "UPLOAD_COVERAGE not set, skipping upload"
        return 0
    fi
    local RET=0
    Verbose ToCodecov || RET=1
    Verbose ToCoveralls || RET=1
    return $RET
}

Verbose lcov --directory "$SOURCE_DIR" --capture --output-file coverage.info &&
Verbose lcov --remove coverage.info '/usr/*' 'test/*' 'benchmarks/*' 'examples/*' 'build/core/joint/JsonParser.*.cpp' 'bindings/java/*' --output-file coverage.info &&
Verbose lcov --list coverage.info && 
Verbose Upload ||
exit 1
