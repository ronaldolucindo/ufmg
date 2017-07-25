//funcao para importar os dados e inseri-los na tabela
function createTable(){
  //importando os dados para um array usando d3
  d3.csv("./data/dados-tp1.csv", function(d) {
    return {
      permalink : d.permalink,
      company : d.company,
      numEmps : +d.numEmps,
      category : d.category,
      city : d.city,
      state : d.state,
      fundedDate : d.fundedDate,
      raisedAmt : d.raisedAmt,
      raisedCurrency : d.raisedCurrency,
      round : d.round
    };
  }, function(data) {
      //selecionando tabela e inserindo os dados
      var table1 = document.getElementById('table1');
      var tbody = document.createElement("tbody");
      table1.appendChild(tbody);
      var row = document.createElement("tr");
      data.forEach(function(items) {
      var row = document.createElement("tr");
        for(var item in items) {
          var cell = document.createElement("td");
          cell.textContent = items[item];
          row.appendChild(cell);
        }
        tbody.appendChild(row);
      });
      //fazendo paginação dos dados
      pagination();
    });
}

//funcao de paginacao da tabela
function pagination(){
  $(document).ready(function(){
    var rowsShown = 10; //numero de entradaspor página
    var rowsTotal = $('#table1 tbody tr').length; //recuperando # de linhas da tabela
    var numPages = rowsTotal/rowsShown; //calculando # de páginas
    $('#table1 tbody tr').hide();
    $('#table1 tbody tr').slice(0, rowsShown).show();
    var startItem = 0;
    var endItem = 0;
    // ao clicar no texto prev verificar se não está na primeira página, caso não esteja mostre página anterior
    $('#pageNavPosition #prev').bind('click', function(){
      if(startItem >= 10){
          startItem = startItem - rowsShown;
          endItem = startItem + rowsShown;
          $('#table1 tbody tr').css('opacity','0.0').hide().slice(startItem, endItem).
              css('display','table-row').animate({opacity:1}, 300);
            }
      });
    // ao clicar no texto next verificar se ainda existem entradas para mostrar, caso tenha mostrar a próxima página  
    $('#pageNavPosition #next').bind('click', function(){
      if(endItem+rowsShown < rowsTotal){
        startItem = startItem + rowsShown;
        endItem = startItem + rowsShown;
        $('#table1 tbody tr').css('opacity','0.0').hide().slice(startItem, endItem).css('display','table-row').animate({opacity:1}, 300);
      }
    });
  });
}


//funcao para pesquisar na tabela
function filterTable( text, _id, noOfHeaderRows ) {
  var table = document.getElementById( _id ), contents, row;
  for (var r = noOfHeaderRows; r < table.rows.length; r++){
    row = table.rows[r];
    contents = row.textContent || row.innerText; 
    contents = contents.toUpperCase();
    text = text.toUpperCase();

    if( contents.indexOf( text ) > -1 ) {
        row.style.display = "";
    } 
    else {
        row.style.display = "none";
        //row.remove();
    }

  }
}

//ordenar os dados da tabela ao clicar no titulo das colunas
$('th').click(function(){
  var table = $(this).parents('table').eq(0);
  var rows = table.find('tr:gt(0)').toArray().sort(comparer($(this).index()));
  this.asc = !this.asc;
  if (!this.asc){
    rows = rows.reverse();
  }
  for (var i = 0; i < rows.length; i++){
    table.append(rows[i]);
  }
  pagination();
})
// função de comparação usada para ordenar os dados
function comparer(index) {
  return function(a, b) {
    var valA = getCellValue(a, index), valB = getCellValue(b, index);
    return $.isNumeric(valA) && $.isNumeric(valB) ? valA - valB : valA.localeCompare(valB);
  }
}

function getCellValue(row, index){ 
  return $(row).children('td').eq(index).html()
}
