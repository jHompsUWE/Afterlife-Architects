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

	//float IGetSoulRateMultiplier();
	//void ISetSoulRateMultiplier(float _soul_rate_multiplier);
	//float IGetPassiveTaxMultiplier();
	//void ISetPassiveTaxMultiplier(float _tax_multiplier);

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

