//
//  ViewController.swift
//  IVAcalculator
//
//  Created by Federico Moretta on 25/12/21.
//

import UIKit

class ViewController: UIViewController {
    
    @IBOutlet weak var ivaResult: UILabel!
    @IBOutlet weak var labelView: UIView!
    @IBOutlet weak var buttonlView: UIButton!
    @IBOutlet weak var textFieldView: UITextField!
    @IBOutlet weak var adviseLabel: UILabel!
    
    var priceNumber: Double?
    
    override func viewDidLoad() {
        super.viewDidLoad()
        self.ivaResult.isHidden = true
        self.labelView.isHidden = true
        self.buttonlView.isHidden = true
        self.adviseLabel.isHidden = true
            
    }
    @IBAction func calculateButton(_ sender: UIButton) {
        guard let number = priceNumber else {
            return
        }
        
        let finalValue: Double = number * 0.22
        self.ivaResult.text = "\(finalValue) €"
        self.ivaResult.isHidden = false
        self.labelView.isHidden = false
        self.adviseLabel.isHidden = false
        print("🦀", finalValue, #function)
    }
    
    @IBAction func priceTextField_EditingChanged(_ sender: UITextField) {
        guard
            let text = sender.text,
            let number = Double.init(text)
        else {
            print("🦀", "priceTextField is not a number")
            self.buttonlView.isHidden = true
            return
        }
        
        guard number != 0.0 else{
            print("🦀", "priceTextField is 0.0")
            self.buttonlView.isHidden = true
            return
        }
        self.buttonlView.isHidden = false
        print("🦀", number, #function)
        
        self.priceNumber = number
    }
    
    @IBAction func priceTextField(_ sender: UITextField) {
        print("🦀", #function)
    }
}

