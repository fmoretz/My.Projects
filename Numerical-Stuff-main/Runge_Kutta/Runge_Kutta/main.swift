//
//  main.swift
//  Runge_Kutta
//
//  Created by Federico Moretta on 21/08/21.
//

import Foundation

//data
let t0: Double = 0;
let y0: Double = 1;
let tf: Double = 10
let dt: Double = 0.1;
let lenght: Double = (tf-t0)/dt

//func: f(t)' = t*(f(t))
public func dydt(t: Double, y: Double) -> Double{
    return t*pow(y,0.5)
}

//pre-processing
public func g1(h: Double, yn: Double, tn: Double) -> Double{
    return h*dydt(t: tn, y: yn)
}

public func g2(h: Double, yn: Double, tn: Double) -> Double{
    return h*dydt(t: tn + 0.5*h, y: yn + 0.5*g1(h: h, yn: yn, tn: tn) )
}

public func g3(h: Double, yn: Double, tn: Double) -> Double{
    return h*dydt(t: tn + 0.5*h, y: yn + 0.5*g2(h: h, yn: yn, tn: tn) )
}

public func g4(h: Double, yn: Double, tn: Double) -> Double{
    return h*dydt(t: tn + h, y: yn + g3(h: h, yn: yn, tn: tn) )
}

public func yn_(h: Double, yn: Double, tn: Double) -> Double{
    return yn + 1/6*( g1(h: h, yn: yn, tn: tn) +
                        2*g2(h: h, yn: yn, tn: tn) +
                        2*g3(h: h, yn: yn, tn: tn) +
                        g4(h: h, yn: yn, tn: tn) )
}

//calculation
var y = [Double]()
var t = [Double]()
var r = [String]()

y.append(y0)
t.append(t0)
r.append("\(t0)\t\(y0)\n")

for i in 0...Int(lenght){
    let ynp1 = yn_(h: dt, yn: y[i], tn: t[i])
    let tnp1 = t[i] + dt
    print(tnp1)
    y.append(ynp1)
    t.append(tnp1)
    r.append("\(tnp1)\t\(ynp1)\n")
}

//write-out
let join_r = r.joined(separator: "\n");


//write-out in project path
let filePath = NSHomeDirectory() + "/Documents/Calcoli/Swift/Runge_kutta/" + "res.txt"
if (FileManager.default.createFile(atPath: filePath, contents: nil, attributes: nil)) {
    print("File created successfully.")
} else {
    print("File not created.")
}
let filePathURL =  URL(fileURLWithPath: filePath)
do {
    for _ in 0...Int(lenght){
        let text: String = join_r
        try text.write(to: filePathURL, atomically: false, encoding: String.Encoding.utf8)
    }
}
