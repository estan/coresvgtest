import SwiftUI
import Darwin

@main
struct TestApp: App {
    init() {
        setlocale(LC_NUMERIC, "sv_SE.UTF-8")
        setenv("CORESVG_VERBOSE", "1", 1)

        Timer.scheduledTimer(withTimeInterval: 5.0, repeats: false) { timer in
            exit(0)
        }
    }
    var body: some Scene {
        WindowGroup {
            TestView()
        }
    }
}
