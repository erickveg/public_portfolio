import pandas as pd
import altair as alt

# Convert the csv file into a DataFrame with pandas
names_data = pd.read_csv("names_year.csv")

## How does your name at your birth year compare to its use historically?

# Separe especific names from the principal dataset
ericks = names_data.query("name == ['Erick','Eric','Erik'] ")

# Create a char displaying years and totals using the queried dataset above
base_chart = (alt.Chart(ericks)
        .encode(
            x= alt.X('year', axis = alt.Axis(format = 'd', title = "Year")), 
            y = alt.Y('Total', axis = alt.Axis(title = "Children with Name 'Erick' & variations")),
            color = "name"
        )
        .mark_line()
)

# Find people who was born only in 1998
query_birth_year = ericks.query("year == 1998")

# Create a vertical line in the year given above
birth_year_line = (alt.Chart(query_birth_year)
                .mark_rule(color = "red")
                .encode( x = "year")
                )
# Find the intersections of 'base chart' and 'birth_year_line' by drawing points
birth_year_intersections = (alt.Chart(query_birth_year)
                        .encode(
                            x = "year",
                            y = "Total",
                        )
                        .mark_circle(color = "black")

# Label each interseccion with the Total of people with that name in the given year                      
)
birth_year_intersections_text = (alt.Chart(query_birth_year)
    .encode(
        x = "year",
        y = "Total",
        text = "Total"
    )
    .mark_text(
        align='left',
        baseline='middle',
        dx=7
        )
)

final_chart = base_chart + birth_year_line + birth_year_intersections + birth_year_intersections_text
final_chart.properties(title = "My name 'Erick' wasn't too popular in 1998",)

## If you talked to someone named Brittany on the phone, what is your guess of his or her age? What ages would you not guess?

# She is probably 25 years old
# Separe especific names from the principal dataset
brittanies = names_data.query("name == 'Brittany'")

# Create a char displaying years and totals using the queried dataset above
brittanies_base_chart = (alt.Chart(brittanies)
.encode( 
    x= alt.X('year', axis = alt.Axis(format = 'd', title = "Year")), 
    y = alt.Y('Total', axis = alt.Axis(title = "Children with Name 'Brittany'")))
.mark_line()
)

brittanies_base_chart.properties(title = "Brittany has its maximum popularity in 1990")

## Mary, Martha, Peter, and Paul are all Christian names. From 1920 to 2000, compare the name usage of each of the four names.

# Create a list with the names to separate from the main dataset
bible_names = ['Mary', 'Martha', 'Peter', 'Paul']

# Use @ to call variables inside a query
bible_names_data = names_data.query("name in @bible_names & 1920 <= year <= 2000")

base_chart = (alt.Chart(bible_names_data)
.encode(
    x= alt.X('year', axis = alt.Axis(format = 'd', title = "Year")), 
    y = alt.Y('Total', axis = alt.Axis(title = "Children with Biblical Name")),
    color = "name")
.mark_line()
)

base_chart.properties(title = "Biblical names were more popular in the 50's")
# Using our list of names we want to determine when and how many children each name
# had on their peaks and how many on average
for iname in bible_names:
    max_use = bible_names_data.query("name == @iname").Total.max()
    max_year = bible_names_data.query("Total == @max_use").year.max()

    mean_use = bible_names_data.query("name == @iname").Total.mean()


    print(f"{iname}: {max_use} max people in {max_year}")    
    print(f"{iname}: {mean_use:.2f} avg people between 1920 and 2000 ")
    print()
    
## Think of a unique name from a famous movie. Plot the usage of that name and see how changes line up with the movie release.

#We will plot the usage of the name "Will" because of Will Smith and compare with his iconic movie "The Pursuit of Happyness" which was released in 2006.

movie_actor_data = names_data.query("name == 'Will'")

base_chart = (alt.Chart(movie_actor_data)
.encode(x= alt.X('year', axis = alt.Axis(format = 'd', title = "Year")), 
    y = alt.Y('Total', axis = alt.Axis(title = "Children with Name 'Will'")))
.mark_line()
)

# The movie "Pursuit of happyness was released in 2006"
release_movie_2006 = movie_actor_data.query("year == 2006")

# The movie "Men in Black" was released in 1997
release_movie_1997 = movie_actor_data.query("year == 1997")

# Create vertical lines to represent the year of movies' release
release_movie_line1 = (alt.Chart(release_movie_2006)
                .mark_rule(color = "red")
                .encode( x = "year")
                )

release_movie_line2 = (alt.Chart(release_movie_1997)
                .mark_rule(color = "red")
                .encode( x = "year")
                )

final_chart2 = base_chart + release_movie_line1 + release_movie_line2
final_chart2.properties(title = "The name 'Will' match its popularity with the movie 'The Pursuit of Happyness' ")