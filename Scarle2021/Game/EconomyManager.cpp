#include "pch.h"
#include "EconomyManager.h"
#include <iostream>

EconomyManager::EconomyManager()
{
}
EconomyManager::~EconomyManager()
{
}

void EconomyManager::UpdateCurrency()
{
	currency = currency += (passive_income * passive_income_multiplier);
	currency = currency -= (passive_tax * passive_tax_multiplier);
}

void EconomyManager::UpdateSouls()
{
}

float EconomyManager::GetCurrency()
{
	return currency;
}
void EconomyManager::SetCurrency(float _currency)
{
	currency = _currency;
}

float EconomyManager::GetPassiveIncome()
{
	return passive_income;
}
void EconomyManager::SetPassiveIncome(float _passive_income)
{
	passive_income = _passive_income;
}

float EconomyManager::GetPassiveTax()
{
	return passive_tax;
}
void EconomyManager::SetPassiveTax(float _passive_tax)
{
	passive_tax = _passive_tax;
}

float EconomyManager::GetPassiveIncomeMultiplier()
{
	return passive_income_multiplier;
}
void EconomyManager::SetPassiveIncomeMultiplier(float _income_multiplier)
{
	passive_income_multiplier = _income_multiplier;
}

float EconomyManager::GetPassiveTaxMultiplier()
{
	return passive_tax_multiplier;
}
void EconomyManager::SetPassiveTaxMultiplier(float _tax_multiplier)
{
	passive_tax_multiplier = _tax_multiplier;
}
