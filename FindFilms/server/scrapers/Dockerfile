# Use an official Python runtime as a parent image
FROM python:2.7-slim

# Set the working directory to /app
WORKDIR /app

# Copy the current directory contents into the container at /app
COPY . /app

# Install any needed packages specified in requirements.txt
RUN pip install --trusted-host pypi.python.org -r requirements.txt

# Define environment variable SERVER_SETTINGS to be in production mode
ENV SERVER_SETTINGS ./configs/production.cfg

# Run python command to update showings
RUN python -c 'from scrapers.prod_db_integration import update_prod_showings; update_prod_showings()'

