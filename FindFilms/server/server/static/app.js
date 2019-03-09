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
    modal.find('#name').text(showingDict['name'])
    modal.find('#date').text(showingDict['date'])
    modal.find('#street').text(showingDict['street'])
    modal.find('#otherAddrInfo').text(showingDict['city'] + ', ' + showingDict['state'] + ' ' + showingDict['zipCode'])
    appendToModalTag(modal, showingDict, 'times', obj => {
        return $('<a>', {
            text: obj,
            href: showingDict['showingUrl'],
        }).addClass('d-inline p-2 m-1 bg-success text-white rounded-pill')
    })
})

$('#movieModal').on('show.bs.modal', function (event) {
    var button = $(event.relatedTarget) // Button that triggered the modal
    var movieDict = button.data('movie') // Extracting showing info as dictionary object
    var modal = $(this)
    modal.find('#title').text(movieDict['title'])
    modal.find('#synopsis').text(movieDict['synopsis'])
    var content = obj => {
        return $('<div>', {
            text: obj,
        })
    }
    appendToModalTag(modal, movieDict, 'genres', content)
    appendToModalTag(modal, movieDict, 'cast', content)
    appendToModalTag(modal, movieDict, 'directors', content)
})
