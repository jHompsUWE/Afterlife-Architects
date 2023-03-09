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

void EconomyManager::IUpdateCurrency()
{
	//currency = currency += (passive_income * passive_income_multiplier);
	//currency = currency -= (passive_tax * passive_tax_multiplier);
	auto current_time = std::chrono::steady_clock::now();
	if (std::chrono::duration_cast<std::chrono::seconds>(current_time - previous_time).count() > 5)
	{
		current_time = previous_time;
		soul_rate = souls_total / year;
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

/*float EconomyManager::IGetSoulRateMultiplier()
{
	return soul_rate_multiplier;
}*/
/*void EconomyManager::ISetSoulRateMultiplier(float _soul_rate_multiplier)
{
	soul_rate_multiplier = _soul_rate_multiplier;
}*/

/*float EconomyManager::IGetPassiveTaxMultiplier()
{
	return soul_rate;
}*/
/*void EconomyManager::ISetPassiveTaxMultiplier(float _tax_multiplier)
{
	tax_multiplier = _tax_multiplier;
}*/
