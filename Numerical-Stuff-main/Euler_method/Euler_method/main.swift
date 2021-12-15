//
//  main.swift
//  Euler_method
//
//  Created by Federico Moretta on 21/08/21.
//

import Foundation
import SwiftPlot
import SVGRenderer

//data
let To = 100.0; //°C
let Tr = 20.0;  //°C
let k = 0.07;   //s-1

//step
let h = 2.0;    //s

//func: dT/dt = -k(T-Tr)
public func dTdt(T: Double) -> Double {
    return -k*(T-Tr)
}

//Euler
var T = [Double]();
T.append(To);
var t = [Double]();
var r = [String]();

for i in 0...100{
    let Tn = T[i] + h*dTdt(T: T[i]);
    T.append(Tn);
    t.append(Double(i));
    r.append("\(Double(i))\t\(Tn)\n")
}
let join_r = r.joined(separator: "\n");


//write-out in project path
let filePath = NSHomeDirectory() + "/Documents/Calcoli/Swift/Euler_method/" + "res.txt"
if (FileManager.default.createFile(atPath: filePath, contents: nil, attributes: nil)) {
    print("File created successfully.")
} else {
    print("File not created.")
}
let filePathURL =  URL(fileURLWithPath: filePath)
do {
    for _ in 0...100{
        let text: String = join_r
        try text.write(to: filePathURL, atomically: false, encoding: String.Encoding.utf8)
    }
}

//write-out in document path
func getDocumentsDirectory() -> URL {
    let paths = FileManager.default.urls(for: .documentDirectory, in: .userDomainMask)
    return paths[0]
}

let fileURL = getDocumentsDirectory().appendingPathComponent("res.txt")
do {
    for _ in 0...100{
        let text: String = join_r
        try text.write(to: fileURL, atomically: false, encoding: String.Encoding.utf8)
    }
}
