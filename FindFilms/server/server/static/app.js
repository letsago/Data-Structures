var socket = io.connect('http://' + document.domain + ':' + location.port)

socket.on('showActiveUserCount', function (data) {
    $("#activeUserCount").text('Active user count: ' + data)
})

$(document).ready(function () {
    // initiate form display when page is ready
    $('#basicSearch').show()
    $('#advancedSearch').hide()
})

$('#expandSearch').click(function () {
    if ($(this).text() === 'Expand Search') {
        $(this).text('Hide')
    } else {
        $(this).text('Expand Search')
    }
    $('#basicSearch').toggle()
    $('#advancedSearch').toggle()
})

function appendToModalTag(modal, dictionary, tagId, makeDom) {
    var id = '#' + tagId
    modal.find(id).html("") // clears html content under id tag in modal
    dictionary[tagId].forEach(element => {
        makeDom(element).appendTo(modal.find(id))
    })
}

$('#theaterModal').on('show.bs.modal', function (event) {
    var button = $(event.relatedTarget) // Button that triggered the modal
    var showingDict = button.data('showing') // Extracting showing info as dictionary object
    var modal = $(this)
    $.ajax({
        type: 'POST',
        url: '/theaterData',
        data: {
            'theaterId': showingDict['theaterId'],
        },
        dataType: 'json'
    }).done(function (data) {
        modal.find('#name').text(data['name'])
        modal.find('#street').text(data['street'])
        modal.find('#otherAddrInfo').text(data['city'] + ', ' + data['state'] + ' ' + data['zipCode'])
    })
    modal.find('#date').text(showingDict['showingDate'])
    appendToModalTag(modal, showingDict, 'times', obj => {
        return $('<a>', {
            text: obj,
            href: showingDict['showingUrl'],
        }).addClass('d-inline p-2 m-1 bg-success text-white rounded-pill')
    })
})

$('#movieModal').on('show.bs.modal', function (event) {
    var button = $(event.relatedTarget) // Button that triggered the modal
    var movie = button.data('movie') // Extracting movie info as dictionary object
    var modal = $(this)
    $.ajax({
        type: 'POST',
        url: '/movieData',
        data: {
            'movieId': movie['id'],
        },
        dataType: 'json'
    }).done(function (data) {
        modal.find('#title').text(data['title'])
        modal.find('#rating').text(data['rating'])
        modal.find('#length').text(data['length'] + ' min')
        modal.find('#rottenTomatoes').text(data['rottenTomatoes'] + '%')
        modal.find('#synopsis').text(data['synopsis'])
        var content = obj => {
            return $('<div>', {
                text: obj,
            })
        }
        appendToModalTag(modal, data, 'genres', content)
        appendToModalTag(modal, data, 'cast', content)
        appendToModalTag(modal, data, 'directors', content)
    })
})
