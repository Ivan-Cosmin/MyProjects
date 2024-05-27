package com.example.tema.adapters

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView
import com.example.tema.models.AnimalModel
import com.example.tema.R
import com.example.tema.helpers.extensions.logErrorMessage
import com.example.tema.models.AnimalOrigin

class AnimalListAdapter(
    private val items: List<AnimalModel>
) : RecyclerView.Adapter<RecyclerView.ViewHolder>() {

    private lateinit var mListener: onItemClickListener
    interface onItemClickListener {
        fun onItemClick(position: Int)
    }

    fun setOnItemClickListener(listener: onItemClickListener) {
        mListener = listener
    }

    override fun getItemCount() = items.size

    override fun getItemViewType(position: Int): Int = items[position].origin.key


    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): RecyclerView.ViewHolder {
        val inflater = LayoutInflater.from(parent.context)
        "onCreateViewHolder".logErrorMessage("AnimalListAdapter")
        return when(viewType) {
            AnimalOrigin.EUROPE.key -> {
                val view = inflater.inflate(R.layout.europe_animal_cell, parent, false)
                EuropeViewHolder(view, mListener)
            }
            AnimalOrigin.AFRICA.key -> {
                val view = inflater.inflate(R.layout.africa_animal_cell, parent, false)
                AfricaViewHolder(view, mListener)
            }
            AnimalOrigin.ANTARCTICA.key -> {
                val view = inflater.inflate(R.layout.antarctica_animal_cell, parent, false)
                AntarcticaViewHolder(view, mListener)
            }
            AnimalOrigin.SOUTH_AMERICA.key -> {
                val view = inflater.inflate(R.layout.south_america_animal_cell, parent, false)
                SouthAmericaViewHolder(view, mListener)
            }
            AnimalOrigin.NORTH_AMERICA.key -> {
                val view = inflater.inflate(R.layout.north_america_animal_cell, parent, false)
                NorthAmericaViewHolder(view, mListener)
            }
            AnimalOrigin.ASIA.key -> {
                val view = inflater.inflate(R.layout.asia_animal_cell, parent, false)
                AsiaViewHolder(view, mListener)
            }
            AnimalOrigin.AUSTRALIA.key -> {
                val view = inflater.inflate(R.layout.australia_animal_cell, parent, false)
                AustraliaViewHolder(view, mListener)
            }
            else -> throw IllegalArgumentException("Invalid view type")
        }
    }

    open inner class ViewHolder(view: View, listener: onItemClickListener) : RecyclerView.ViewHolder(view) {
        protected val animalNameTextView : TextView
        protected val animalOriginTextView : TextView
        init {
            animalNameTextView = view.findViewById(R.id.animal_name)
            animalOriginTextView = view.findViewById(R.id.animal_origin)

            itemView.setOnClickListener {
                val position = adapterPosition
                if (position != RecyclerView.NO_POSITION) {
                    listener.onItemClick(position)
                }
            }
        }
    }

    inner class EuropeViewHolder(view: View, listener: onItemClickListener) : ViewHolder(view, mListener) {
        fun bind(animal: AnimalModel) {
            animalNameTextView.text = animal.name
            animalOriginTextView.text = "Europe"
        }
    }

    inner class AfricaViewHolder(view: View, listener: onItemClickListener) : ViewHolder(view, mListener) {
        fun bind(animal: AnimalModel) {
            animalNameTextView.text = animal.name
            animalOriginTextView.text = "Africa"
        }
    }

    inner class AntarcticaViewHolder(view: View, listener: onItemClickListener) : ViewHolder(view, mListener) {
        fun bind(animal: AnimalModel) {
            animalNameTextView.text = animal.name
            animalOriginTextView.text = "Antarctica"
        }
    }

    inner class SouthAmericaViewHolder(view: View, listener: onItemClickListener) : ViewHolder(view, mListener) {
        fun bind(animal: AnimalModel) {
            animalNameTextView.text = animal.name
            animalOriginTextView.text = "South America"
        }
    }

    inner class NorthAmericaViewHolder(view: View, listener: onItemClickListener) : ViewHolder(view, mListener) {
        fun bind(animal: AnimalModel) {
            animalNameTextView.text = animal.name
            animalOriginTextView.text = "North America"
        }
    }

    inner class AsiaViewHolder(view: View, listener: onItemClickListener) : ViewHolder(view, mListener) {
        fun bind(animal: AnimalModel) {
            animalNameTextView.text = animal.name
            animalOriginTextView.text = "Asia"
        }
    }

    inner class AustraliaViewHolder(view: View, listener: onItemClickListener) : ViewHolder(view, mListener) {
        fun bind(animal: AnimalModel) {
            animalNameTextView.text = animal.name
            animalOriginTextView.text = "Australia"
        }
    }

    override fun onBindViewHolder(holder: RecyclerView.ViewHolder, position: Int) {
        val animal = items[position]
        when(holder) {
            is EuropeViewHolder -> (animal.origin == AnimalOrigin.EUROPE).let { holder.bind(animal) }
            is AfricaViewHolder -> (animal.origin == AnimalOrigin.AFRICA).let { holder.bind(animal) }
            is AntarcticaViewHolder -> (animal.origin == AnimalOrigin.ANTARCTICA).let { holder.bind(animal) }
            is SouthAmericaViewHolder -> (animal.origin == AnimalOrigin.SOUTH_AMERICA).let { holder.bind(animal) }
            is NorthAmericaViewHolder -> (animal.origin == AnimalOrigin.NORTH_AMERICA).let { holder.bind(animal) }
            is AsiaViewHolder -> (animal.origin == AnimalOrigin.ASIA).let { holder.bind(animal) }
            is AustraliaViewHolder -> (animal.origin == AnimalOrigin.AUSTRALIA).let { holder.bind(animal)}
        }
        "onBindViewHolder; position = $position".logErrorMessage("AnimalListAdapter")
    }
}