//
//  main.swift
//  Swift_first
//
//  Created by Federico Moretta on 18/08/21.
//

import Foundation

//boundaries
let n = 1000.0;
let a = 0.0;
let b = 1.0;

//step eval
let h = (b-a)/n;

//func: f1(x) = x^3
public func f1(x: Double) -> Double {
    return pow(x,3);
};

//area eval
let f_a = f1(x: a);
let f_b = f1(x: b);

var dsum = 0.0;
for i in 0...Int(n){
    let step = a + Double(i)*h;
    let df_x = 2*f1(x: step);
    dsum = dsum + df_x;
}

let I: Double = h/2*(f_a + dsum + f_b);
print("Integral value: \(I)");
