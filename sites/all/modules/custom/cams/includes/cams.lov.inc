<?php
/*
 * CAMS Integration
 * Integration between CAMS and MyAUP
 *
 * @author: Pierre-Yves Vasener <pvasener@aup.edu>
 */
 
/*
 * LOV (List of Values) FUNCTIONS
 */

/**
 * TODO
 *
 */
function cams_lov_states() {
  if (!cams_is_available())
    return FALSE;
  
  $sql = "SELECT UniqueID id, DisplayText name
  FROM Glossary
  WHERE Category=1003";
  $query = mssql_query($sql);
  
  $states = array();
  while ($state = mssql_fetch_object($query)) {
    $states[$state->id] = $state->name;
  }

  return $states;
}

/**
 * TODO
 *
 */
function cams_lov_countries() {
  if (!cams_is_available())
    return FALSE;

  $sql = "SELECT UniqueID id, Description name
  FROM Glossary
  WHERE Category=1002";
  $query = mssql_query($sql);

  $countries = array();
  while ($country = mssql_fetch_object($query)) {
    $countries[$country->id] = $country->name;
  }

  return $countries;
}

/**
 * TODO
 *
 */
function cams_lov_addressTypes() {
  if (!cams_is_available())
    return FALSE;

  $sql = "SELECT UniqueID id, DisplayText name
  FROM Glossary
  WHERE Category=14";
  $query = mssql_query($sql);

  $addressTypes = array();
  while ($addressType = mssql_fetch_object($query)) {
    $addressTypes[$addressType->id] = $addressType->name;
  }

  return $addressTypes;
}