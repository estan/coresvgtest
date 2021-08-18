import AppKit
import SwiftUI
import Darwin

@main
struct TestApp: App {
    init() {
        setlocale(LC_NUMERIC, "sv_SE.UTF-8")
    }
    var body: some Scene {
        WindowGroup {
            View {
                Image(nsImage: NSImage(data: "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n<svg version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 10 10\"><path fill=\"white\" d=\"M 4 2 L 6.195312 2 L 6.195312 8.996094 L 4 8.996094 Z\"/></svg>"))
            }
        }
    }
}
