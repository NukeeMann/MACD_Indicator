#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

static const int N = 1000;


float EMA(float* data, int day, int interval) {
	float alfa_minus_one = 1.0f - (2.0f / (interval - 1.0f));
	float powerOfAlfa = alfa_minus_one;
	float counter = data[day];
	float denominator = 1;

	for (int i = 1; i <= interval; i++) {
		if (day - i < 0) {
			counter += data[0] * powerOfAlfa;
		}
		else {
			counter += data[day - i] * powerOfAlfa;
		}

		denominator += powerOfAlfa;
		powerOfAlfa *= alfa_minus_one;
	}
	return counter / denominator;
}
float RS(float* data, int day, int interval) {
	float win = 0.0f;
	float los = 0.0f;
	for (int i = 1; i <= interval; i++) {
		if (day - i < 0)
			break;
		float difference = data[day] - data[day - i];
		if (difference >= 0)
			win += difference;
		else
			los -= difference;
	}
	if (los == 0.0f)
		return 0.0f;
	return win / los;
}

float MACD(float* data, int day, int dolny_interval, int gorny_interval) {
	return EMA(data, day, dolny_interval) - EMA(data, day, gorny_interval);
}
float SIGNAL(float* data, int day, int interval) {
	return EMA(data, day, interval);
}
float RSI(float* data, int day, int interval) {
	float rs_var = RS(data, day, interval);
	return 100.0f - (100.0f / (1.0f + rs_var));
}

void play_on_market(float money, float* data, float* macd, float* signal, float* rsi) {
	bool s_below = true;
	float investment = 0.0f;
	float price = 0;
	float starting_money = money;

	for (int i = 1; i < N - 1; i++) {


		if (s_below && signal[i] > macd[i] && rsi[i] < 30 && data[i] > price / 0.8f) {
			money += investment * data[i]; // Quantity times price
			investment = 0;
			s_below = false;
		}
		else if (!s_below && signal[i] < macd[i]) {
			float divider = data[i];
			investment += (money * 0.1f) / data[i];
			price = data[i];
			money -= money * 0.1f;
			s_below = true;
		}
	}
	money += investment * data[N - 1];
	cout << "From " << starting_money << "$ made: " << money << "$" << endl;
	return;
}

int main() {

	// ZCZYTYWANIE DANYCH
	char fileName[255];
	cout << "Provide file name: ";
	cin >> fileName;
	fstream input;
	input.open(fileName, ios::in);

	if (!input.good())
	{
		cout << "[ERROR] Can't finde file '" << fileName << "'." << endl;
		return 0;
	}

	float data[N];
	string tmp;
	getline(input, tmp);
	for (int i = 0; i < N; i++) {
		getline(input, tmp, ',');
		getline(input, tmp, ',');
		data[i] = stof(tmp);
		getline(input, tmp, ',');
		getline(input, tmp, ',');
		getline(input, tmp, ',');
		getline(input, tmp, ',');
		getline(input, tmp);
	}

	input.close();


	// Calculation of MACD, SIGNAL and RSI
	//fstream MACD_r;
	//fstream SIGNAL_r;
	//fstream RSI_r;
	fstream data_r;
	//MACD_r.open("MACD_results.txt", ios::out);
	//SIGNAL_r.open("SIGNAL_results.txt", ios::out);
	//RSI_r.open("RSI_results.txt", ios::out);
	data_r.open("data.txt", ios::out);

	float macd_samples[N];
	float signal_samples[N];
	float rsi_samples[N];
	for (int i = 0; i < N; i++) {
		macd_samples[i] = MACD(data, i, 12, 26);
		macd_samples[i] = roundf(macd_samples[i] * 1000) / 1000;
		//MACD_r << (float)macd_samples[i] << endl;


		signal_samples[i] = SIGNAL(macd_samples, i, 9);
		signal_samples[i] = roundf(signal_samples[i] * 1000) / 1000;
		//SIGNAL_r << (float)signal_samples[i] << endl;

		rsi_samples[i] = RSI(data, i, 14);
		//RSI_r << rsi_samples[i] << endl;

		data_r << data[i] << endl;

	}

	data_r.close();
	//RSI_r.close();
	//SIGNAL_r.close();
	//MACD_r.close();
	
	float money = 1000.0f;
	cout << "Cash contribution: ";
	cin >> money;
	play_on_market(money, data, macd_samples, signal_samples, rsi_samples);

	return 0;
}