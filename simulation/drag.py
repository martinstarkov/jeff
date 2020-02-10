import numpy as np
import math

class FlightConfiguration(object):
    
	def __init__(self, length, area): # constructor
		self.length = length
		self.area = area

    def get_length(self):
        return self.length

class FlightConditions(object):

	def __init__(self, velocity, kinematic_viscosity, mach): # constructor
		self.velocity = velocity
		self.kinematic_viscosity = kinematic_viscosity
		self.mach = mach

	def get_velocity(self):
		return self.velocity

	def get_kinematic_viscosity(self):
		return self.kinematic_viscosity

	def get_mach(self):
		return self.mach

class Drag(object): # general drag related formulas

    def __init__(self): # no need for constructor as only classmethods are used (for the moment)
        pass

    @classmethod
    def get_reynolds_number(cls, velocity, length, kinematic_viscosity):
        return (velocity * length / kinematic_viscosity)

class FrictionDrag(object):

    def __init__(self, conditions, configuration): # constructor
        self.conditions = conditions
        self.configuration = configuration

	def get_value(self): # generate a friction drag value
        # safe reynolds number to this variable
		self.Re = Drag.get_reynolds_number(self.conditions.get_velocity(), self.configuration.get_length(), self.conditions.get_kinematic_viscosity())
        
        self.Cf = -1 # set scope of Cf to outer scope (don't declare variables inside if-statements)

        if self.Re < 1e4:
            self.Cf = 1.33e-2
        elif self.Re < 5.39e5:
            self.Cf = 1.328 / sqrt(abs(self.Re))
        else:
            self.Cf = 1.0 / pow(1.5 * math.log(self.Re) - 5.6) - 1700 / self.Re
        # continue formulas and manipulation from here

        return self.Cf

# initalize flight conditions and configuration
conditions = FlightConditions(266, 14.8e-6, 0.79)
configuration = FlightConfiguration(2.14, 0)

# create a friction drag object
fd = FrictionDrag(conditions, configuration)

# print the value of friction drag
print(fd.get_value())