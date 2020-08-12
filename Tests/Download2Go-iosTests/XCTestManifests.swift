import XCTest

#if !canImport(ObjectiveC)
public func allTests() -> [XCTestCaseEntry] {
    return [
        testCase(Download2Go_iosTests.allTests),
    ]
}
#endif
