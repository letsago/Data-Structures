# Use an official Python runtime as a parent image
FROM python:2.7-slim

# Set the working directory to /app
WORKDIR /app

# Copy parent directory contents into the container at /app
COPY .. /app

# Install any needed packages specified in requirements.txt
RUN pip install --trusted-host pypi.python.org -r requirements.txt

# Make port 3001 available to the world outside this container
EXPOSE 3001

# Define environment variable SERVER_SETTINGS to be in production mode
ENV SERVER_SETTINGS ./configs/production.cfg

# Run launch.py when the container launches
CMD ["python", "launch.py"]

