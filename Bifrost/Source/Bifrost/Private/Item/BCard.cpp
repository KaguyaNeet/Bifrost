// Fill out your copyright notice in the Description page of Project Settings.

#include "BCard.h"
#include "BUnit.h"

void UBCard::Initialize(const FCardAttribute& cardAttribute, CardFunc cardFunc)
{
	m_CardAttribute = cardAttribute;
	m_CardFunction = cardFunc;
}
