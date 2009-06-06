// $Id$

Drupal.behaviors.shorten = function (context) {
  var input = $('#edit-shortened-url')[0];
  input.select();
  input.focus();
  $('#edit-shortened-url').click(function() {
    input.select();
    input.focus();
  });
}