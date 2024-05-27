package com.example.tema

import android.os.Bundle
import android.view.LayoutInflater
import android.view.ViewGroup
import android.widget.RelativeLayout
import android.widget.TextView
import androidx.activity.OnBackPressedCallback
import androidx.fragment.app.Fragment
import androidx.navigation.fragment.findNavController
import androidx.navigation.fragment.navArgs
import com.example.tema.models.AnimalOrigin

@Suppress("DEPRECATION")
class AnimalDetailsFragment : Fragment() {

    val arguments: AnimalDetailsFragmentArgs by navArgs()

    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ) = inflater.inflate(R.layout.fragment_animal_details, container, false)

    override fun onViewCreated(view: android.view.View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        val lLayout: RelativeLayout = view.findViewById<RelativeLayout>(R.id.rl_animal)
        var color = android.graphics.Color.BLACK
        var origin = ""
        when (arguments.animalOrigin) {
            AnimalOrigin.AFRICA.key -> {
                color = resources.getColor(R.color.yellow)
                origin = "Africa"
            }
            AnimalOrigin.SOUTH_AMERICA.key -> {
                color = resources.getColor(R.color.orange)
                origin = "South America"
            }
            AnimalOrigin.NORTH_AMERICA.key -> {
                color = resources.getColor(R.color.brown)
                origin = "North America"
            }
            AnimalOrigin.AUSTRALIA.key -> {
                color = resources.getColor(R.color.purple)
                origin = "Australia"
            }
            AnimalOrigin.ASIA.key -> {
                color = resources.getColor(R.color.red)
                origin = "Asia"
            }
            AnimalOrigin.EUROPE.key -> {
                color = resources.getColor(R.color.green)
                origin = "Europe"
            }
            AnimalOrigin.ANTARCTICA.key -> {
                color = resources.getColor(R.color.blue)
                origin = "Antarctica"
            }
        }
        view.findViewById<TextView>(R.id.animal_name).text = arguments.animalName.toString()
        view.findViewById<TextView>(R.id.animal_origin).text = origin
        view.findViewById<TextView>(R.id.animal_description).text = arguments.animalDescription.toString()

        lLayout.setBackgroundColor(color)

        requireActivity().onBackPressedDispatcher
            .addCallback(viewLifecycleOwner, object : OnBackPressedCallback(true) {
                override fun handleOnBackPressed() {
                    findNavController().popBackStack()
                }
            })
    }


}
