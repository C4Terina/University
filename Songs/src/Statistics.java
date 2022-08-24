import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.*;
import java.util.*;
import java.util.function.Function;
import java.util.stream.Collectors;

public class Statistics extends JFrame {
    private JLabel sumLabel, genreLabel, minLabel, maxLabel;
    private JTextArea area;
    private ArrayList<Song> songList = new ArrayList<>();
    private JButton exitBtn;

    public Statistics(){
        prepareUI();
    }

    public void prepareUI() { //Αρχικοποιούμε το UI
        this.setSize(780,420);
        this.setTitle("Statistics");
        this.setDefaultCloseOperation(JFrame.HIDE_ON_CLOSE);
        this.setLocationRelativeTo(null);
        this.setResizable(true); // Αφαιρούμε από τον χρήστη την δυνατότητα να κάνει resize το window

        JPanel topPanel = new JPanel();
        topPanel.setLayout(new BoxLayout(topPanel, BoxLayout.Y_AXIS));

        JPanel bottomPanel = new JPanel();
        bottomPanel.setLayout(new FlowLayout(FlowLayout.CENTER));

        sumLabel = new JLabel();
        genreLabel = new JLabel();
        minLabel = new JLabel();
        maxLabel = new JLabel();

        exitBtn = new JButton("Exit");
        exitBtn.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                setVisible(false);
                dispose(); //Destroy the JFrame object
            }
        });

        area = new JTextArea();
        area.setEditable(false);

        JLabel columnsLbl = new JLabel("\nSongId" + "     " + "Duration" + "            " +
                 "Title" + "          " + "Release date" + "    " + "Artist" + "         "
                + "Genre");

        topPanel.add(sumLabel);
        topPanel.add(genreLabel);
        topPanel.add(minLabel);
        topPanel.add(maxLabel);
        topPanel.add(columnsLbl);

        bottomPanel.add(exitBtn);

        loadFromFile("songlist.txt");
        setStatistics();

        Image icon = Toolkit.getDefaultToolkit().getImage("icon.png");
        this.setIconImage(icon);

        this.add(topPanel, BorderLayout.PAGE_START);
        this.add(area, BorderLayout.CENTER);
        this.add(bottomPanel, BorderLayout.PAGE_END);
        this.setVisible(true);
    }

    private void loadFromFile(String fileName) {
        try {
            BufferedReader reader = new BufferedReader(new FileReader(fileName));

            String line;
            String[] token;
            Song song;

            while (reader.ready()) {
                line = reader.readLine();
                area.append(line);
                area.append("\n");

                //Χωρίζουμε το κάθε field του array list σε διαφορετικά tokens για να μπορούμε να τα επεξεργαστούμε
                token = line.split("\t");
                if (token.length == 6) {
                    song = new Song(token[0], token[1], token[2], token[3], token[4], token[5]);
                    songList.add(song);
                }
            }

        } catch (FileNotFoundException ex) {
            ex.printStackTrace();
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }

    private void setStatistics() {
        int sum = 0, min = Integer.MAX_VALUE, max = Integer.MIN_VALUE;

        String titleOfMax = "", titleOfMin = "";
        String genreOfMax = "", genreOfMin = "";

        for (Song song : songList) {
            int duration = Integer.parseInt(song.getDuration());
            if (max < duration){
                max = duration;
                titleOfMax = song.getTitle();
                genreOfMax = song.getGenre();
            }

            if (min > duration){
                min = duration;
                titleOfMin = song.getTitle();
                genreOfMin = song.getGenre();
            }

        }

        //Μετράει τα genres και επιστρέφει χάρτη με κλειδί το όνομα του genre και value το πλήθος του genre
        Map<String, Long> result = songList.stream() //απο list σε stream
                .map(Song::getGenre) // απο stream σε χάρτη (map)
                .collect(Collectors.groupingBy(Function.identity(),
                        Collectors.counting()));
        Long genreMax = 0L;
        String maxGenre = "";
        for(String genre:result.keySet()){
            if(result.get(genre) > genreMax){
                genreMax = result.get(genre);
                maxGenre = genre;
            }
        }
        //Τα εμφανίζουμε στο text area
        sumLabel.setText("Total songs: " + songList.size());
        genreLabel.setText("The genre with the most songs is " + maxGenre + " with a total of " + result.get(maxGenre) + " songs");
        minLabel.setText("The title of the song with the least duration is " + titleOfMin + " and the genre is " + genreOfMin);
        maxLabel.setText("The title of the song with the most duration is " + titleOfMax + " and the genre is " + genreOfMax);
    }
}