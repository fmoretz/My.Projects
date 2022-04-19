//
//  ContentView.swift
//  WeatherCheckApp
//
//  Created by Federico Moretta on 26/12/21.
//

import SwiftUI

struct ContentView: View {
    
    @State private var isNight = false
    
    var body: some View {
        ZStack{
            backgroundView(isNight: $isNight)
            
            VStack{ // Meteo oggi
                CityNameText(cityName: "Milano")
                mainWeather(imageName: isNight ? "cloud.moon.fill" : "cloud.sun.fill",
                            temperature: 25)
    
                HStack(spacing: 20){ // Previsione prossimi cinque giorni
                    // Lunedì
                    weatherDayView(dayOfWeek: "LUN",
                                   imageName: "sun.max.fill",
                                   dayTemperature: 30)
                    // Martedì
                    weatherDayView(dayOfWeek: "MAR",
                                   imageName: "cloud.sun.fill",
                                   dayTemperature: 24)
                    // Mercoledì
                    weatherDayView(dayOfWeek: "MER",
                                   imageName: "cloud.fill",
                                   dayTemperature: 22)
                    // Giovedì
                    weatherDayView(dayOfWeek: "GIO",
                                   imageName: "cloud.rain.fill",
                                   dayTemperature: 18)
                    //Venerdì
                    weatherDayView(dayOfWeek: "VEN",
                                   imageName: "cloud.fog.fill",
                                   dayTemperature: 19)
                }
                Spacer()
                
                Button{
                    isNight.toggle()
                } label: {
                    weatherButton(title: "Change day time",
                                  textColor: .blue,
                                  backColor: .white)
                }
                Spacer()
            }
        }
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}

// structure for daily prediction
struct weatherDayView: View {
    
    var dayOfWeek: String
    var imageName: String
    var dayTemperature: Int
    
    var body: some View {
        VStack{ // Lunedì
            Text(dayOfWeek)
                .foregroundColor(.white)
                .font(.system(size: 20,
                              weight: .bold,
                              design: .default))
            Image(systemName: imageName)
                .renderingMode(.original)
                .resizable()
                .aspectRatio(contentMode: .fit)
                .frame(width: 50,
                       height: 50)
            Text("\(dayTemperature)°")
                .font(.system(size: 20,
                              weight: .bold,
                              design: .default))
                .foregroundColor(.white)
        }
    }
}

struct backgroundView: View {
    
    @Binding var isNight: Bool
    
    var body: some View {
        LinearGradient(gradient: Gradient(colors: [isNight ? .black : .blue,
                                                   isNight ? Color("darkBlue") : Color("lightBlue")]),
                       startPoint: .topLeading,
                       endPoint: .bottomTrailing)
            .ignoresSafeArea(.all)
    }
}

struct CityNameText: View {
    
    var cityName: String
    
    var body: some View {
        Text(cityName)
            .font(.system(size: 35,
                          weight: .bold,
                          design: .default))
            .foregroundColor(.white)
            .padding()
    }
}

struct mainWeather: View {
    
    var imageName: String
    var temperature: Int
    
    var body: some View {
        VStack(spacing: 5){
            Image(systemName: imageName)
                .renderingMode(.original)
                .resizable()
                .aspectRatio(contentMode: .fit)
                .frame(width: 180,
                       height: 180)
            Text("\(temperature)°")
                .font(.system(size: 70,
                              weight: .bold,
                              design: .default))
                .foregroundColor(.white)
                .padding(.bottom)
        }.padding(.bottom, 40)
    }
}
