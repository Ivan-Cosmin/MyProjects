package com.example.tema.models

enum class AnimalOrigin(
    val key: Int
) {
    EUROPE(0),
    AFRICA(1),
    ASIA(2),
    NORTH_AMERICA(3),
    SOUTH_AMERICA(4),
    AUSTRALIA(5),
    ANTARCTICA(6)
}

data class AnimalModel(
    val id: Int,
    val name: String,
    val description: String,
    val origin: AnimalOrigin
)