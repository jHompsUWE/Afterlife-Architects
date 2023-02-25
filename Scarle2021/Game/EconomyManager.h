#pragma once
class EconomyManager
{
public:
	EconomyManager();
	~EconomyManager();

	void UpdateCurrency();
	void UpdateSouls();

	float GetCurrency();
	void SetCurrency(float _currency);

	float GetPassiveIncome();
	void SetPassiveIncome(float _passive_income);
	float GetPassiveTax();
	void SetPassiveTax(float _passive_tax);

	float GetPassiveIncomeMultiplier();
	void SetPassiveIncomeMultiplier(float _income_multiplier);

	float GetPassiveTaxMultiplier();
	void SetPassiveTaxMultiplier(float _tax_multiplier);

private:
	float currency = 1000.0f;

	float passive_income = 0.0f;
	float passive_tax = 0.0f;

	float passive_income_multiplier = 1.0f;
	float passive_tax_multiplier = 1.0f;


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
};

