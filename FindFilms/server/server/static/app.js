$(document).ready(function () {
    // initiate form display when page is ready
    $('#basicSearch').show();
    $('#advancedSearch').hide();

    $('#expandSearch').click(function () {
        if ($(this).text() === 'Expand Search') {
            $(this).text('Hide');
        } else {
            $(this).text('Expand Search');
        }
        $('#basicSearch').toggle();
        $('#advancedSearch').toggle();
    });
});
