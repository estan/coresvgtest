all:
	mkdir -p TestApp.app/Contents/MacOS
	swiftc -framework SwiftUI -o TestApp.app/Contents/MacOS/TestApp TestView.swift TestApp.swift
	actool --compile TestApp.app/Contents/Resources --platform macosx --target-device mac --minimum-deployment-target 10.15 Assets.xcassets
