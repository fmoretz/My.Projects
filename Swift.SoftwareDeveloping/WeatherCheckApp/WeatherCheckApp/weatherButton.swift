//
//  weatherButton.swift
//  WeatherCheckApp
//
//  Created by Federico Moretta on 28/12/21.
//

import SwiftUI

struct weatherButton: View {
    
    var title: String
    var textColor: Color
    var backColor: Color
    
    var body: some View {
            Text(title)
                .frame(width: 280,
                       height: 50)
                .foregroundColor(textColor)
                .background(backColor)
                .font(.system(size: 20,
                              weight: .bold,
                              design: .default))
                .cornerRadius(100)
    }
}
