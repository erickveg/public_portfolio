
def calculate_pyramid_volume(l,w,h):
    """ Define the main function to calculate the pyramid volume
    and convert the result from centimeters into inches.
    Params: l(float): length, w(float): width, h(float): height
    """

    # Calculate the pyramid base area
    base_area= calculate_base_area(l,w)

    # Use the formula to calculate the pyramid volume
    volume_cm = (base_area*h)/3

    # Convert the result to inches
    volume_in = convert_cm_to_in(volume_cm)

    return volume_in    

def calculate_base_area(l,w):
    # Multiply the lenght and the width of the base to 
    # optain the area
    base_area = l*w

    return base_area

def convert_cm_to_in(result_cm):
    #Use the formula to convert centimeters into inches
    result_in = result_cm/2.54

    return result_in

# Test Case 1
result = calculate_pyramid_volume(3,5,10) #19.685
print(f"The pyramid volume in inches is: {result:.3f}")