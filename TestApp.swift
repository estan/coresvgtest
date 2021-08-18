import SwiftUI
import Darwin

@main
struct TestApp: App {
    init() {
        setlocale(LC_NUMERIC, "sv_SE.UTF-8")
    }
    var body: some Scene {
        WindowGroup {
            TestView()
        }
    }
}
