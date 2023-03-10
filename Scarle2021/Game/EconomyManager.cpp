#include "pch.h"
#include "EconomyManager.h"
#include <iostream>

EconomyManager& EconomyManager::Get()
{
	static EconomyManager instance;
	return instance;
}

void EconomyManager::UpdateCurrency()
{
	Get().IUpdateCurrency();
}
void EconomyManager::UpdateSouls()
{
	Get().IUpdateSouls();
}

int EconomyManager::GetYear()
{
	return Get().IGetYear();
}

int EconomyManager::GetCurrency()
{
	return Get().IGetCurrency();
}

void EconomyManager::SetCurrency(float _currency)
{
	Get().ISetCurrency(_currency);
}

int EconomyManager::GetSouls()
{
	return Get().IGetSouls();
}

void EconomyManager::SetSouls(int _souls)
{
	Get().ISetSouls(_souls);
}

float EconomyManager::GetTax()
{
	return Get().IGetTax();
}

void EconomyManager::SetTax(float _tax)
{
	Get().ISetTax(_tax);
}

float EconomyManager::GetSoulRateMultiplier()
{
	return Get().IGetSoulRateMultiplier();
}

void EconomyManager::SetSoulRateMultiplier(float _soul_rate_multiplier)
{
	Get().ISetSoulRateMultiplier(_soul_rate_multiplier);
}

int EconomyManager::GetSoulsHeavenGreen()
{
	return Get().IGetSoulsHeavenGreen();
}

void EconomyManager::SetSoulsHeavenGreen(int _souls_heaven_green)
{
	Get().ISetSoulsHeavenGreen(_souls_heaven_green);
}

int EconomyManager::GetSoulsHellGreen()
{
	return Get().IGetSoulsHellGreen();
}

void EconomyManager::SetSoulsHellGreen(int _souls_hell_green)
{
	Get().ISetSoulsHellGreen(_souls_hell_green);
}

int EconomyManager::GetSoulsHeavenYellow()
{
	return Get().IGetSoulsHeavenYellow();
}

void EconomyManager::SetSoulsHeavenYellow(int _souls_heaven_yellow)
{
	Get().ISetSoulsHeavenYellow(_souls_heaven_yellow);
}

int EconomyManager::GetSoulsHellYellow()
{
	return Get().IGetSoulsHellYellow();
}

void EconomyManager::SetSoulsHellYellow(int _souls_hell_yellow)
{
	Get().ISetSoulsHellYellow(_souls_hell_yellow);
}

int EconomyManager::GetSoulsHeavenOrange()
{
	return Get().IGetSoulsHeavenOrange();
}

void EconomyManager::SetSoulsHeavenOrange(int _souls_heaven_orange)
{
	Get().ISetSoulsHeavenOrange(_souls_heaven_orange);
}

int EconomyManager::GetSoulsHellOrange()
{
	return Get().IGetSoulsHellOrange();
}

void EconomyManager::SetSoulsHellOrange(int _souls_hell_orange)
{
	Get().ISetSoulsHellOrange(_souls_hell_orange);
}

int EconomyManager::GetSoulsHeavenBrown()
{
	return Get().IGetSoulsHeavenBrown();
}

void EconomyManager::SetSoulsHeavenBrown(int _souls_heaven_brown)
{
	Get().ISetSoulsHeavenBrown(_souls_heaven_brown);
}

int EconomyManager::GetSoulsHellBrown()
{
	return Get().IGetSoulsHellBrown();
}

void EconomyManager::SetSoulsHellBrown(int _souls_hell_brown)
{
	Get().ISetSoulsHellBrown(_souls_hell_brown);
}

int EconomyManager::GetSoulsHeavenPurple()
{
	return Get().IGetSoulsHeavenPurple();
}

void EconomyManager::SetSoulsHeavenPurple(int _souls_heaven_purple)
{
	Get().ISetSoulsHeavenPurple(_souls_heaven_purple);
}

int EconomyManager::GetSoulsHellPurple()
{
	return Get().IGetSoulsHellPurple();
}

void EconomyManager::SetSoulsHellPurple(int _souls_hell_purple)
{
	Get().ISetSoulsHellPurple(_souls_hell_purple);
}

int EconomyManager::GetSoulsHeavenRed()
{
	return Get().IGetSoulsHeavenRed();
}

void EconomyManager::SetSoulsHeavenRed(int _souls_heaven_red)
{
	Get().ISetSoulsHeavenRed(_souls_heaven_red);
}

int EconomyManager::GetSoulsHellRed()
{
	return Get().IGetSoulsHellRed();
}

void EconomyManager::SetSoulsHellRed(int _souls_hell_red)
{
	Get().ISetSoulsHellRed(_souls_hell_red);
}

int EconomyManager::GetSoulsHeavenBlue()
{
	return Get().IGetSoulsHeavenBlue();
}

void EconomyManager::SetSoulsHeavenBlue(int _souls_heaven_blue)
{
	Get().ISetSoulsHeavenBlue(_souls_heaven_blue);
}

int EconomyManager::GetSoulsHellBlue()
{
	return Get().IGetSoulsHellBlue();
}

void EconomyManager::SetSoulsHellBlue(int _souls_hell_blue)
{
	Get().ISetSoulsHellBlue(_souls_hell_blue);
}

void EconomyManager::IUpdateCurrency()
{
	//currency = currency += (passive_income * passive_income_multiplier);
	//currency = currency -= (passive_tax * passive_tax_multiplier);
	auto current_time = std::chrono::steady_clock::now();
	if (std::chrono::duration_cast<std::chrono::seconds>(current_time - previous_time).count() > year_update_interval)
	{
		current_time = previous_time;
		soul_rate = (souls_total / year) * soul_rate_multiplier;
		currency = currency + soul_rate;
		year++;
	}
}

void EconomyManager::IUpdateSouls()
{
	souls_total = (souls_heaven_blue + souls_heaven_brown + souls_heaven_green + souls_heaven_orange + souls_heaven_purple
		+ souls_heaven_red + souls_hell_yellow) + (souls_hell_blue + souls_hell_brown + souls_hell_green + souls_hell_orange +
			souls_hell_purple + souls_hell_red + souls_hell_yellow);
}

int EconomyManager::IGetYear()
{
	return year;
}

int EconomyManager::IGetCurrency()
{
	return currency;
}
void EconomyManager::ISetCurrency(float _currency)
{
	currency = _currency;
}

int EconomyManager::IGetSouls()
{
	return souls_total;
}
void EconomyManager::ISetSouls (int _total_souls)
{
	souls_total = _total_souls;
}

float EconomyManager::IGetTax()
{
	return tax;
}
void EconomyManager::ISetTax(float _tax)
{
	tax = _tax;
}

float EconomyManager::IGetSoulRateMultiplier()
{
	return soul_rate_multiplier;
}
void EconomyManager::ISetSoulRateMultiplier(float _soul_rate_multiplier)
{
	soul_rate_multiplier = _soul_rate_multiplier;
}

int EconomyManager::IGetSoulsHeavenGreen()
{
	return souls_heaven_green;
}

void EconomyManager::ISetSoulsHeavenGreen(int _souls_heaven_green)
{
	souls_heaven_green = _souls_heaven_green;
}

int EconomyManager::IGetSoulsHellGreen()
{
	return souls_hell_green;
}

void EconomyManager::ISetSoulsHellGreen(int _souls_hell_green)
{
	souls_hell_green = _souls_hell_green;
}

int EconomyManager::IGetSoulsHeavenYellow()
{
	return souls_heaven_yellow;
}

void EconomyManager::ISetSoulsHeavenYellow(int _souls_heaven_yellow)
{
	souls_heaven_yellow = _souls_heaven_yellow;
}

int EconomyManager::IGetSoulsHellYellow()
{
	return souls_hell_yellow;
}

void EconomyManager::ISetSoulsHellYellow(int _souls_hell_yellow)
{
	souls_hell_yellow = _souls_hell_yellow;
}

int EconomyManager::IGetSoulsHeavenOrange()
{
	return souls_heaven_orange;
}

void EconomyManager::ISetSoulsHeavenOrange(int _souls_heaven_orange)
{
	souls_heaven_orange = _souls_heaven_orange;
}

int EconomyManager::IGetSoulsHellOrange()
{
	return souls_hell_orange;
}

void EconomyManager::ISetSoulsHellOrange(int _souls_hell_orange)
{
	souls_hell_orange = _souls_hell_orange;
}

int EconomyManager::IGetSoulsHeavenBrown()
{
	return souls_heaven_brown;
}

void EconomyManager::ISetSoulsHeavenBrown(int _souls_heaven_brown)
{
	souls_heaven_brown = _souls_heaven_brown;
}

int EconomyManager::IGetSoulsHellBrown()
{
	return souls_hell_brown;
}

void EconomyManager::ISetSoulsHellBrown(int _souls_hell_brown)
{
	souls_hell_brown = _souls_hell_brown;
}

int EconomyManager::IGetSoulsHeavenPurple()
{
	return souls_heaven_purple;
}

void EconomyManager::ISetSoulsHeavenPurple(int _souls_heaven_purple)
{
	souls_heaven_purple = _souls_heaven_purple;
}

int EconomyManager::IGetSoulsHellPurple()
{
	return souls_hell_purple;
}

void EconomyManager::ISetSoulsHellPurple(int _souls_hell_purple)
{
	souls_hell_purple = _souls_hell_purple;
}

int EconomyManager::IGetSoulsHeavenRed()
{
	return souls_heaven_red;
}

void EconomyManager::ISetSoulsHeavenRed(int _souls_heaven_red)
{
	souls_heaven_red = _souls_heaven_red;
}

int EconomyManager::IGetSoulsHellRed()
{
	return souls_hell_red;
}

void EconomyManager::ISetSoulsHellRed(int _souls_hell_red)
{
	souls_hell_red = _souls_hell_red;
}

int EconomyManager::IGetSoulsHeavenBlue()
{
	return souls_heaven_blue;
}

void EconomyManager::ISetSoulsHeavenBlue(int _souls_heaven_blue)
{
	souls_heaven_blue = _souls_heaven_blue;
}

int EconomyManager::IGetSoulsHellBlue()
{
	return souls_hell_blue;
}

void EconomyManager::ISetSoulsHellBlue(int _souls_hell_blue)
{
	souls_hell_blue = _souls_hell_blue;
}

/*float EconomyManager::IGetPassiveTaxMultiplier()
{
	return soul_rate;
}*/
/*void EconomyManager::ISetPassiveTaxMultiplier(float _tax_multiplier)
{
	tax_multiplier = _tax_multiplier;
}*/
