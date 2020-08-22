# MACD and RSI stock market indicators
The report below is based on data from PKN_Orlen_SA.csv file

## MACD and SIGNAL
Graph that shows MACD and SINGAL lines.
Horizontal axis - quotation date. 
Vertical axis - value of the indicators.

Grey line - SIGNAL

Orange line - MACD

![MACD_SIGNAL](https://github.com/NukeeMann/MACD_Indicator/blob/master/readme_img/image001.png)

Actual PKN_Orlen_SA.csv data:

![PKN_Orlen_SA](https://github.com/NukeeMann/MACD_Indicator/blob/master/readme_img/image003.png)

## Comparison of the results

![MACD_SIGNAL_2](https://github.com/NukeeMann/MACD_Indicator/blob/master/readme_img/image005.png)

Red circles are points where MACD tells to sell our actions, and green circle tells when to buy them. 
Red line shows where stock drops and green one where stock grow.

Because of the large time interval and many cross points i have marked only the most important, key points in which MACD or data graph has changed the most.

As we can see MACD indicator in most cases well predicts what will happen with PKN Orlen shares on market. Greatest profit is achieved when MACD is rapidly dropping / growing. 
But there are a bit too many cross points MACD with SIGNAL in which case we can suffer small losses. 
In my opinion MACD indicator is useful in technical analysis when used with caution and checking the trend using other tools.

## Stock market game algorithm

I have implemented an algorithm which simulates market stocks and let us test startegies which we want to use on real market. My startegie uses MACD and RSI indicators.
RSI lower border is set to 30. When sale process of action goes with simultaneous checking both indicators and when both of them points out that it is a good moment for sell and the price is at least 80 % of the one we bought our stocks with, we sell all of our resources.
However decision about buying stocks is based only on MACD and SIGNAL crossing investing only a percent of our budget. 
This way we will not spend all our credits and we will avoid some unfavorable sale moments.

Below are shown some examples with diffrent investing percentage of our budget.

#### For 20% of our budget

![20p](https://github.com/NukeeMann/MACD_Indicator/blob/master/readme_img/image007.png)

#### For 40% of our budget

![40p](https://github.com/NukeeMann/MACD_Indicator/blob/master/readme_img/image009.png)

#### For 60% of our budget

![60p](https://github.com/NukeeMann/MACD_Indicator/blob/master/readme_img/image011.png)

#### For 80% of our budget

![80p](https://github.com/NukeeMann/MACD_Indicator/blob/master/readme_img/image013.png)

As we can see, implemented strategy is safe enough that with high percent of investing money we are still winning.
