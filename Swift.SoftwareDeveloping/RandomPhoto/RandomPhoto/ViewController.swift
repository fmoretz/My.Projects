//
//  ViewController.swift
//  RandomPhoto
//
//  Created by Federico Moretta on 24/12/21.
//

import UIKit

class ViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
        
        view.addSubview(button)
        button.addTarget(self, action: #selector(didTapButton), for: .touchUpInside)
        view.addSubview(boxResult)
    }
    
    
    
    override func viewDidLayoutSubviews() {
        super.viewDidLayoutSubviews()
        button.frame = CGRect(
            x: 20,
            y: view.frame.size.height-100-view.safeAreaInsets.bottom,
            width: view.frame.size.width-250,
            height: 50)
        boxResult.frame = CGRect(
            x: 100,
            y: view.frame.size.height-100-view.safeAreaInsets.bottom,
            width: view.frame.size.width-250,
            height: 50)
        
    }
    
    @objc func didTapButton(){
        Addition(firstNumber: 2, secondNumber: 2)
    }
    
    func Addition(firstNumber: Int, secondNumber: Int) -> Int{
        let a = firstNumber
        let b = secondNumber
        let c = a+b
        return c
    }
    
    private let button: UIButton = {
        let button = UIButton()
        button.backgroundColor = .red
        button.setTitle("Calculate", for: .normal)
        button.setTitleColor(.black, for: .normal)
        return button
    }()
    
    private let boxResult: UILabel = {
        let boxResult = UILabel()
        boxResult.backgroundColor = .none
        boxResult.layer.borderColor = .init(red: 0, green: 0, blue: 0, alpha: 100)
        return boxResult
    }()

}

