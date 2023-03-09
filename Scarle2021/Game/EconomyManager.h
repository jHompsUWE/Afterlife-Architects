#pragma once
#include <chrono>

class EconomyManager
{
public:
	static EconomyManager& Get();

	static void UpdateCurrency();
	static void UpdateSouls();

	static int GetYear();

	static int GetCurrency();
	static void SetCurrency(float _currency);

	static int GetSouls();
	static void SetSouls(int _souls);

	static float GetTax();
	static void SetTax(float _tax);

	static float GetSoulRateMultiplier();
	static void SetSoulRateMultiplier(float _soul_rate_multiplier);

	static int GetSoulsHeavenGreen();
	static void SetSoulsHeavenGreen(int _souls_heaven_green);
	static int GetSoulsHellGreen();
	static void SetSoulsHellGreen(int _souls_hell_green);

	static int GetSoulsHeavenYellow();
	static void SetSoulsHeavenYellow(int _souls_heaven_yellow);
	static int GetSoulsHellYellow();
	static void SetSoulsHellYellow(int _souls_hell_yellow);

	static int GetSoulsHeavenOrange();
	static void SetSoulsHeavenOrange(int _souls_heaven_orange);
	static int GetSoulsHellOrange();
	static void SetSoulsHellOrange(int _souls_hell_orange);

	static int GetSoulsHeavenBrown();
	static void SetSoulsHeavenBrown(int _souls_heaven_brown);
	static int GetSoulsHellBrown();
	static void SetSoulsHellBrown(int _souls_hell_brown);

	static int GetSoulsHeavenPurple();
	static void SetSoulsHeavenPurple(int _souls_heaven_purple);
	static int GetSoulsHellPurple();
	static void SetSoulsHellPurple(int _souls_hell_purple);

	static int GetSoulsHeavenRed();
	static void SetSoulsHeavenRed(int _souls_heaven_red);
	static int GetSoulsHellRed();
	static void SetSoulsHellRed(int _souls_hell_red);

	static int GetSoulsHeavenBlue();
	static void SetSoulsHeavenBlue(int _souls_heaven_blue);
	static int GetSoulsHellBlue();
	static void SetSoulsHellBlue(int _souls_hell_blue);


private:
	EconomyManager() = default;
	~EconomyManager() = default;

	void IUpdateCurrency();
	void IUpdateSouls();

	int IGetYear();

	int IGetCurrency();
	void ISetCurrency(float _currency);

	int IGetSouls();
	void ISetSouls(int _souls_total);

	float IGetTax();
	void ISetTax(float _tax);

	float IGetSoulRateMultiplier();
	void ISetSoulRateMultiplier(float _soul_rate_multiplier);
	//float IGetPassiveTaxMultiplier();
	//void ISetPassiveTaxMultiplier(float _tax_multiplier);

	int IGetSoulsHeavenGreen();
	void ISetSoulsHeavenGreen(int _souls_heaven_green);
	int IGetSoulsHellGreen();
	void ISetSoulsHellGreen(int _souls_hell_green);

	int IGetSoulsHeavenYellow();
	void ISetSoulsHeavenYellow(int _souls_heaven_yellow);
	int IGetSoulsHellYellow();
	void ISetSoulsHellYellow(int _souls_hell_yellow);

	int IGetSoulsHeavenOrange();
	void ISetSoulsHeavenOrange(int _souls_heaven_orange);
	int IGetSoulsHellOrange();
	void ISetSoulsHellOrange(int _souls_hell_orange);

	int IGetSoulsHeavenBrown();
	void ISetSoulsHeavenBrown(int _souls_heaven_brown);
	int IGetSoulsHellBrown();
	void ISetSoulsHellBrown(int _souls_hell_brown);

	int IGetSoulsHeavenPurple();
	void ISetSoulsHeavenPurple(int _souls_heaven_purple);
	int IGetSoulsHellPurple();
	void ISetSoulsHellPurple(int _souls_hell_purple);

	int IGetSoulsHeavenRed();
	void ISetSoulsHeavenRed(int _souls_heaven_red);
	int IGetSoulsHellRed();
	void ISetSoulsHellRed(int _souls_hell_red);

	int IGetSoulsHeavenBlue();
	void ISetSoulsHeavenBlue(int _souls_heaven_blue);
	int IGetSoulsHellBlue();
	void ISetSoulsHellBlue(int _souls_hell_blue);

	int year = 1;
	int currency = 1000;

	float soul_rate = 0.0f;
	float tax = 0.0f;

	float soul_rate_multiplier = 1.0f;
	float tax_multiplier = 1.0f;


	int souls_heaven_green = 0;
	int souls_heaven_yellow = 0;
	int souls_heaven_orange = 0;
	int souls_heaven_brown = 0;
	int souls_heaven_purple = 0;
	int souls_heaven_red = 0;
	int souls_heaven_blue = 0;

	int souls_hell_green = 0;
	int souls_hell_yellow = 0;
	int souls_hell_orange = 0;
	int souls_hell_brown = 0;
	int souls_hell_purple = 0;
	int souls_hell_red = 0;
	int souls_hell_blue = 0;

	int souls_total = 0;

	std::chrono::time_point<std::chrono::steady_clock> previous_time = std::chrono::steady_clock::now();;
};

