let votes = {
    frankenstein: 0,
    pride: 0,
    moby: 0
  };

let totalVotes = 0;

const ctx = document.getElementById('resultsChart').getContext('2d');
let resultsChart = new Chart(ctx, {
  type: 'bar',
  data: {
      labels: ['Frankenstein', 'Pride and Predjudice', 'Moby Dick'],
      datasets: [{
          label: 'Votes',
          data: [votes.frankenstein, votes.pride, votes.moby],
          backgroundColor: [
              '#3498db',
              '#e74c3c',
              '#2ecc71'
          ],
          borderColor: [
              '#2980b9',
              '#c0392b',
              '#27ae60'
          ],
          borderWidth: 2
      }]
  },
  options: {
      responsive: true,
      scales: {
          y: {
            beginAtZero: true
          }
      }
  }
});

function vote(candidate) {
  votes[candidate] += 1;
  totalVotes += 1;
  localStorage.setItem('hasVoted', 'true');

  updateResults();
}

function updateResults() {
  resultsChart.data.datasets[0].data = [votes.frankenstein, votes.pride, votes.moby];
  resultsChart.update();

  document.getElementById('totalVotes').textContent = totalVotes;
}

function showDetailedResults() {
  document.getElementById('votesFrankenstein').textContent = votes.frankenstein;
  document.getElementById('votesPride').textContent = votes.pride;
  document.getElementById('votesMoby').textContent = votes.moby;

  document.getElementById('percentFrankenstein').textContent = totalVotes > 0 ? ((votes.frankenstein / totalVotes) * 100).toFixed(2) + '%' : '0%';
  document.getElementById('percentPride').textContent = totalVotes > 0 ? ((votes.pride / totalVotes) * 100).toFixed(2) + '%' : '0%';
  document.getElementById('percentMoby').textContent = totalVotes > 0 ? ((votes.moby / totalVotes) * 100).toFixed(2) + '%' : '0%';

  document.getElementById('detailedResults').style.display = 'block';
}

function resetVotes() {
  votes = { frankenstein: 0, pride: 0, moby: 0 };
  totalVotes = 0;
  localStorage.removeItem('hasVoted');

  updateResults();
  document.getElementById('detailedResults').style.display = 'none';
  alert("Votes have been reset!");
}